/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:01:35 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/13 10:08:30 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;


	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (0);
	i = 0;
	j = 0;
	if(s1)
	{
		
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	}
	if(s2)
	{

	while (s2 && s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	}
	res[i + j] = 0;
	return (res);
}
