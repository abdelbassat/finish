/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:49:51 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/19 23:43:24 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_nested_syntax(t_list **head)
{
	char		*cmd;
	t_quotes	qutes;
	t_list		*list;
	t_list		*ss;

	list = *head;
	ss = split_end_or(list->content, "<> ", 0);
	global->data->red = ft_check_syntax(ss, 2);
	if (!global->data->red)
		ft_split_rediction(list->content, head);
	cmd = join_command(list->command);
	if (cmd && !global->data->red)
	{
		ft_check_string(cmd);
		if (ft_count_qutes(cmd, &qutes) == 1 && !global->data->red)
		{
			cmd = ft_substr(cmd, 1, ft_strlen(cmd) - 2);
			ft_syntax(cmd);
		}
	}
}

void	ft_syntax(char *line)
{
	t_list	*head;
	t_list	*list;

	head = split_end_or(line, "|&", 1);
	global->data->red = ft_check_syntax(head, 4);
	while (head && !global->data->red)
	{
		if (head->x != 4)
		{
			list = split_end_or(head->content, "|", 0);
			global->data->red = ft_check_syntax(list, 4);
			while (list && !global->data->red)
			{
				if (list->x != 4)
					ft_nested_syntax(&list);
				list = list->next;
			}
		}
		head = head->next;
	}
}

int	ft_check_syntax(t_list *head, int flag)
{
	int	i;

	i = 0;
	while (head)
	{
		if ((head->x == flag && (!head->next || head->next->x == flag))
			|| (head->x == 4 && i == 0))
			return (1);
		head = head->next;
		i++;
	}
	return (0);
}

void	ft_check_string(char *line)
{
	int			i;
	t_quotes	qutes;

	i = 0;
	initialize(&qutes, NULL);
	while (line[i])
	{
		ft_check_quotes(line[i], &qutes);
		i++;
	}
	if (qutes.cp || qutes.cq || qutes.cs || (qutes.en % 2) || (qutes.bk % 2))
		global->data->red = 1;
}

int	ft_check_wildcard(char *line)
{
	int			i;
	t_quotes	qutes;

	i = 0;
	initialize(&qutes, NULL);
	while (line[i])
	{
		ft_check_quotes(line[i], &qutes);
		if (qutes.cq || qutes.cs)
			return (1);
		i++;
	}
	return (0);
}
