/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:43:33 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/17 20:30:16 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_check(char c, t_quotes *data)
{
	if (c == 34 && !data->cq && !data->cs)
		data->cq++;
	else if (c == 34 && !data->cs)
		data->cq--;
	if (c == 39 && !data->cq && !data->cs)
		data->cs++;
	else if (c == 39 && !data->cq)
		data->cs--;
}

int	ft_check_str(char *str)
{
	t_quotes	qutes;
	int			i;

	i = 0;
	qutes.cp = 0;
	qutes.cq = 0;
	qutes.cs = 0;
	qutes.en = 0;
	qutes.bk = 0;
	while (str[i])
	{
		ft_check_quotes(str[i], &qutes);
		if (qutes.cp)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_qutes(char *line, t_quotes *qutes)
{
	int	i;
	int	flag;

	flag = ft_check_str(line);
	i = 0;
	initialize(qutes, NULL);
	while (line[i])
	{
		ft_check(line[i], qutes);
		if (line[i] == '(' && !qutes->cq && !qutes->cs)
		{
			if (line[i + 1] == ')')
				global->data->red = 1;
			qutes->cp++;
		}
		else if (line[i] == ')' && !qutes->cq && !qutes->cs)
			qutes->cp--;
		else if (!qutes->cp && flag)
			global->data->red = 1;
		i++;
	}
	return (flag);
}
