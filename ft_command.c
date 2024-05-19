/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:14:52 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/20 00:53:11 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_handel_redic(t_list **redic, int flag)
{
	ft_exec_redic(*redic, flag);
}

void	exec_command(t_list *head, char *cmd, char **command)
{
	int	flag;

	flag = 0;
	global->data->pid = fork();
	if (!global->data->pid)
	{
		if (global->data->out == -1 || global->data->in == -1)
			exit(1);
		if (ft_strrchr(cmd, '/') && opendir(cmd))
			ft_print_error(cmd, "Is a directory");
		if (head && cmd[0])
		{
			if (global->data->in != 0)
			{
				dup2(global->data->in, 0);
				close(global->data->in);
			}
			if (global->data->out != 1)
			{
				dup2(global->data->out, 1);
				close(global->data->out);
				close(global->data->fd[0]);
			}
			flag = ft_builting(head);
			if (flag == 1)
			{
				execve(cmd, command, last_command(global->data->env_list));
				ft_print_error(cmd, strerror(errno));
			}
		}
		exit(0);
	}
}

void	ft_fork_exit(int er)
{
	global->data->pid = fork();
	if (global->data->pid == 0)
		exit(er);
}

void	ft_exec_command(t_list *head)
{
	char	**command;
	char	*cmd;

	command = last_command(head);
	cmd = ft_check_command(command[0]);
	if (global->data->size == 1)
		if (head && !ft_builting(head))
			return ;
	exec_command(head, cmd, command);
}

void	ft_command(t_list *head)
{
	int	out;
	int	in;

	out = dup(1);
	in = dup(0);
	ft_handel_redic(&(head->redic), 1);
	if (head->int_file == 2 && global->data->in != -1)
		global->data->in = head->in;
	ft_exec_command(head->command);
	dup2(out, 1);
	close(out);
	dup2(in, 0);
	close(in);
}
