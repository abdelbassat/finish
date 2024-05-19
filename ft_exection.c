/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:58:14 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/19 22:14:49 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_exec_recursive(t_list **head)
{
	int	p;

	p = fork();
	if (p == 0)
	{
		ft_nested_pip_ex((*head)->new_list->new_list, global->data->out,
			global->data->in);
		exit(global->data->status);
	}
	wait(&global->data->status);
}

void	exec_utils(t_list *head, int fd1, int fd0)
{
	int	out;
	int	in;

	if (head->new_list->x != 4)
	{
		if (head->new_list->next)
		{
			pipe(global->data->fd);
			global->data->out = global->data->fd[1];
		}
		else
			global->data->out = fd1;
		if (head->new_list->x == 1)
		{
			out = dup(1);
			in = dup(0);
			ft_handel_redic(&head->new_list->redic, 1);
			if (head->new_list->int_file == 2)
				global->data->in = head->new_list->in;
			if (global->data->in == -1 || global->data->out == -1)
				return ;
			ft_exec_recursive(&head);
			dup2(out, 1);
			close(out);
			dup2(in, 0);
			close(in);
		}
		else
			ft_command(head->new_list);
		close_fd(&head, fd0);
	}
}

void	ft_nested_pip_ex(t_list *head, int fd1, int fd0)
{
	t_list	*tmp;

	global->data->out = fd1;
	global->data->in = fd0;
	global->data->exec = 0;
	while (head)
	{
		check_eo(head, fd1, fd0);
		if (global->data->exec == 0)
		{
			tmp = head->new_list;
			global->data->size = ft_lstsize(tmp);
			while (head->new_list)
			{
				exec_utils(head, fd1, fd0);
				head->new_list = head->new_list->next;
			}
			wait_proccess();
		}
		head = head->next;
	}
}
