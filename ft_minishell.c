/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:33:37 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/13 17:57:23 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		mode;

void	handle_signal(int sig)
{
	if (sig == SIGINT && mode == 0)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
void	handle_signal_cat(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
void	ft_handle_signals(void)
{
	if (signal(SIGINT, handle_signal) == SIG_ERR)
		printf("Error catch signal\n");
	signal(SIGINT, handle_signal);
	// if (data->data_mode == 0)
	// else if (data->data_mode == 1)
	// 	signal(SIGINT, handle_signal_cat);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_data	data;
	t_list	*head;
	char	*save;

	(void)av;
	head = NULL;
	data.env = env;
	initialize(NULL, &data);
	ft_buffer_to_list(&data.env_list, env);
	if (ac != 1)
		return (1);
	while (1)
	{
		mode = 0;
		ft_handle_signals();
		line = ft_pwd(0);
		save = line;
		line = readline(line);
		free(save);
		add_history(line);
		if (!line)
			exit(1);
		(void)head;
		ft_syntax(line, &data);
		if (data.red == 1)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
			data.red = 0;
		}
		else
		{
			mode = 1;
			head = ft_nested_pip(line, &data);
			ft_nested_pip_ex(head, &data, STDOUT_FILENO, STDIN_FILENO);
			ft_free_trees(&head);
			data.in = 0;
			data.out = 1;
		}
	}
	return (0);
}
