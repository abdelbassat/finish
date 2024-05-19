/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:35:45 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/19 21:18:53 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	check_eo(t_list *head, int fd1, int fd0)
{
	char	*op;

	op = (char *)head->content;
	if (strcmp(op, "&&") == 0)
	{
		if (global->data->status == 0)
			global->data->exec = 0;
		else
			global->data->exec = 1;
	}
	else if (strcmp(op, "||") == 0)
	{
		if (global->data->status != 0)
			global->data->exec = 0;
		else
			global->data->exec = 1;
	}
	if (global->data->exec == 0)
	{
		global->data->out = fd1;
		global->data->in = fd0;
	}
}

void	wait_proccess(void)
{
	int	status;
	int	tmp;

	tmp = 0;
	while (1)
	{
		status = wait(&tmp);
		if (status == global->data->pid)
			global->data->status = tmp;
		if (status == -1)
			break ;
	}
	if (global->data->status > 255)
		global->data->status = global->data->status >> 8;
}

void	close_fd(t_list **tmp, int fd0)
{
	t_list	*head;

	head = *tmp;
	if (head->new_list->next != NULL)
	{
		close(global->data->fd[1]);
		if (global->data->in != fd0)
			close(global->data->in);
		global->data->in = global->data->fd[0];
	}
	else if (head->next == NULL)
	{
		if (global->data->in != fd0)
			close(global->data->in);
	}
}
