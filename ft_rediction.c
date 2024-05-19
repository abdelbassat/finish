/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rediction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:19:20 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/19 23:44:42 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"




void	ft_exec_utils(t_list *head, int flag)
{
	char	*red;

	red = head->content;
	if (flag == 1)
	{
		if (!strcmp(red, ">>"))
		{
			global->data->out = access_outfile_herdoc(head->next->content);
			if (global->data->out != -1)
			{
				dup2(global->data->out, 1);
				close(global->data->out);
			}
		}
		else if (!strcmp(red, ">"))
		{
			global->data->out = access_outfile(head->next->content);
			if (global->data->out != -1)
			{
				if (dup2(global->data->out, 1) == -1)
					close(global->data->out);
				global->data->out = 1;
			}
		}
		else if (!strcmp(red, "<"))
		{
			global->data->in = access_intfile(head->next->content);
			if (global->data->in != -1)
			{
				dup2(global->data->in, 0);
				close(global->data->in);
				global->data->in = 0;
			}
		}
	}
	else
	{
		if (!strcmp(red, "<<"))
		{
			global->data->in = ft_read_stdin(head->next->content);
			unlink(global->data->save);
		}
	}
}

void	ft_exec_redic(t_list *head, int flag)
{
	while (head)
	{
		ft_exec_utils(head, flag);
		if (global->data->out == -1 || global->data->in == -1)
			break ;
		head = head->next;
	}
}

char	*ft_generate(void)
{
	int		fd;
	char	*buff;
	int		i;

	fd = open("/dev/random", O_RDWR);
	buff = malloc(11);
	ft_lstadd_back(&(global->head_free), ft_lstnew_v1(buff));
	read(fd, buff, 10);
	buff[10] = 0;
	i = 0;
	while (buff[i])
	{
		if (ft_isalnum(buff[i]) == 0)
			buff[i] = 'a';
		i++;
	}
	return (ft_strjoin("/tmp/.", buff));
}

int	ft_read_stdin(char *end)
{
	char	*buff;
	int		fd;

	global->data->save = ft_generate();
	fd = open(global->data->save, O_CREAT | O_RDWR, 0600);
	while (1)
	{
		buff = readline("> ");
		if (!buff || !strcmp(buff, end))
			break ;
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
	}
	close(fd);
	fd = open(global->data->save, O_RDWR, 0400);
	return (fd);
}

void	ft_split_rediction(char *line, t_list **command)
{
	t_list	*head;

	head = split_end_or(line, ">< ", 0);
	while (head)
	{
		if (head->x == 4 && head->next->x != 4)
		{
			global->syntax = 1;
			if (strcmp(head->content, "<<") == 0)
			{
				(*command)->int_file = 2;
				ft_lstnew_back(&((*command)->here_doc), head->content, 0);
				head = head->next;
				ft_lstnew_back(&((*command)->here_doc), head->content, 4);
			}
			else
			{
				(*command)->int_file = 1;
				ft_lstnew_back(&((*command)->redic), head->content, 0);
				head = head->next;
				ft_lstnew_back(&((*command)->redic), head->content, 4);
			}
		}
		else
		{
			global->syntax = 1;
			ft_lstnew_back(&(*command)->command, head->content, 0);
		}
		head = head->next;
	}
}
