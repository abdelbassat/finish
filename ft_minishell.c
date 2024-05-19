/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:33:37 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/19 22:51:19 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define EXTERN
#include "ft_minishell.h"

void	ft_exec_pro(char *line)
{
	t_list	*head;

	head = NULL;
	ft_syntax(line);
	if (global->data->red == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		global->data->red = 0;
		global->data->status = 2;
	}
	else
	{
		global->mode = 1;
		head = ft_nested_pip(line);
		ft_nested_pip_ex(head, 1, 0);
	}
}

char	*ft_handel_tab(char *line)
{
	int		size;
	char	*new;
	int		i;

	size = ft_strlen(line);
	new = malloc(size + 1);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		new[i] = line[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	(void)env;
	global = malloc(sizeof(g_global));
	global->data = malloc(sizeof(t_data));
	global->head_free = NULL;
	global->shell = 0;
	global->shell++;
	global->mode = 0;
	global->syntax = 0;
	global->backup = NULL;
	global->data->env_list = NULL;
	initialize(NULL, global->data);
	ft_buffer_to_list(&global->data->env_list, env);
	if (ac != 1)
		return (1);
	// printf("/proc/%d/fd\n", getpid());
	while (1)
	{
		global->mode = 0;
		ft_handle_signals();
		line = ft_pwd();
		line = readline(line);
		add_history(line);
		if (!line)
			break ;
		line = ft_handel_tab(line);
		ft_exec_pro(line);
	}
	ft_free();
	return (1);
}

void	ft_free(void)
{
	t_list	*tmp;
	t_list	*head;

	head = global->head_free;
	tmp = NULL;
	while (head)
	{
		tmp = head->next;
		free(head->addr);
		ft_lstdelone(head, free);
		head = tmp;
	}
}
