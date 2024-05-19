/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:50:20 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/17 14:50:29 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ini_str(t_str *data)
{
	data->str = NULL;
	data->join = NULL;
	data->flag = 0;
	data->c = 0;
	data->i = 0;
}

void	charset(char c, char *set, t_str *strr)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
		{
			strr->c = set[i];
			break ;
		}
		i++;
	}
}

void	ft_check_quotes(char c, t_quotes *data)
{
	if (c == '(' && !data->cq && !data->cs)
		data->cp++;
	else if (c == ')' && !data->cq && !data->cs)
		data->cp--;
	if (c == 34 && !data->cq && !data->cs)
		data->cq++;
	else if (c == 34 && !data->cs)
		data->cq--;
	if (c == 39 && !data->cq && !data->cs)
		data->cs++;
	else if (c == 39 && !data->cq)
		data->cs--;
	if (c == '&' && !data->cq && !data->cs && !data->cp)
		data->en++;
	if (c == '`' && !data->cq && !data->cs && !data->cp)
		data->en++;
}
