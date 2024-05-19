/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:03:56 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/19 22:40:53 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_check_01(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_list *head)
{
	int size = ft_lstsize(head);
	if (size > 2)
		ft_fork_exit(1);
	else
	{
		head = head->next;
		if (!head)
			exit(0);
		else if (ft_check_01(head->content) == 1)
			exit(2);
		exit(ft_atoi(head->content));
	}
}