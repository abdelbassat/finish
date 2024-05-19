/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:28:31 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/19 16:10:02 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_pwd(void)
{
	char	*buff;
	char	*path;
	char	*arrow;

	buff = malloc(4000);
	ft_lstadd_back(&(global->head_free), ft_lstnew_v1(buff));
	if (!getcwd(buff, 4000))
		buff = global->backup;
	else
		global->backup = ft_strdup(buff);
	buff = &ft_strrchr(buff, '/')[1];
	path = ft_strjoin(buff, " ");
	arrow = ft_strjoin("\e[1;32m", "\u2794");
	arrow = ft_strjoin(arrow, " ");
	arrow = ft_strjoin(arrow, "\e[1;33m");
	path = ft_strjoin(arrow, path);
	path = ft_strjoin(path, "\033[0m");
	path = ft_strjoin("\033[0;37m", path);
	return (path);
}
