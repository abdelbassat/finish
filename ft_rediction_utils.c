/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rediction_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:40:54 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/17 15:17:55 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_error(char *path)
{
	char	*join;

	join = ft_strjoin("minishell: ", path);
	perror(join);
}

int	access_outfile_herdoc(char *path)
{
	int	fd;

	fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		ft_error(path);
	return (fd);
}

int	access_intfile(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error(path);
	return (fd);
}

int	access_outfile(char *path)
{
	int	fd;

	fd = open(path, O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		ft_error(path);
	return (fd);
}
