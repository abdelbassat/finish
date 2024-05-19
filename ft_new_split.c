/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:59:46 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/20 00:39:53 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// void	ft_lstnew_back(t_list **head, char *cont, int flag)
// {
// 	t_list	*node;

// 	node = ft_lstnew(cont);
// 	if (node->content[0])
// 	{
// 		node->x = flag;
// 		ft_lstadd_back(head, node);
// 	}
// }
// void	utils_split(t_str *strr, t_list **head, int flag)
// {
// 	if (strr->join)
// 		ft_lstnew_back(head, strr->join, 0);
// 	if (strr->str[strr->i + 1] || strr->str[strr->i] == strr->c)
// 	{
// 		if (strr->str[strr->i] != ' ')
// 			strr->join = ft_new_strjoin(NULL, strr->str[strr->i]);
// 		if (strr->str[strr->i + 1] == strr->c && strr->c != ' ')
// 		{
// 			strr->i = strr->i + 1;
// 			strr->join = ft_strjoin(strr->join, strr->join);
// 		}
// 		if (strr->str[strr->i] != ' ')
// 			ft_lstnew_back(head, strr->join, flag);
// 	}
// 	strr->join = NULL;
// 	strr->flag = 0;
// }

// t_list	*split_end_or(char *line, char *set, int check)
// {
// 	t_list		*head;
// 	t_quotes	qutes;
// 	t_str		strr;
// 	int			ff;

// 	head = NULL;
// 	ini_str(&strr);
// 	initialize(&qutes, NULL);
// 	strr.str = line;
// 	ff = 4;
// 	if (!strcmp(set, "<> "))
// 		ff = 2;
// 	while (line[strr.i])
// 	{
// 		ft_check_quotes(line[strr.i], &qutes);
// 		charset(line[strr.i], set, &strr);
// 		if (line[strr.i] == strr.c && (line[strr.i + 1] == strr.c || check == 0)
// 			&& !qutes.cp && !qutes.cq && !qutes.cs)
// 			strr.flag = 1;
// 		else
// 			strr.join = ft_new_strjoin(strr.join, line[strr.i]);
// 		if (strr.flag == 1 || !line[strr.i + 1])
// 			utils_split(&strr, &head, ff);
// 		strr.i++;
// 	}
// 	return (head);
// }

// void	ft_print_error(char *cmd, char *str)
// {
// 	int	ex;

// 	ex = 126;
// 	if (errno == 2)
// 		ex = 127;
// 	ft_putstr_fd("minishell : ", 2);
// 	ft_putstr_fd(cmd, 2);
// 	ft_putstr_fd(" : ", 2);
// 	if (!ft_strrchr(cmd, '/'))
// 	{
// 		str = "command not found";
// 		ex = 127;
// 	}
// 	ft_putstr_fd(str, 2);
// 	ft_putstr_fd("\n", 2);
// 	exit(ex);
// }

// char	*ft_new_strjoin(char *str, char c)
// {
// 	int		i;
// 	char	*join;

// 	join = malloc(ft_strlen(str) + 2);
// 	ft_lstadd_back(&(global->head_free), ft_lstnew_v1(join));
// 	i = 0;
// 	if (str != NULL)
// 	{
// 		while (str[i])
// 		{
// 			join[i] = str[i];
// 			i++;
// 		}
// 	}
// 	if (c == 0)
// 		join[i] = c;
// 	else
// 	{
// 		join[i] = c;
// 		i++;
// 		join[i] = 0;
// 	}
// 	return (join);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:59:46 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/17 16:20:57 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_lstnew_back(t_list **head, char *cont, int flag)
{
	t_list	*node;

	node = ft_lstnew(cont);
	if (node->content[0])
	{
		node->x = flag;
		ft_lstadd_back(head, node);
	}
}

void	utils_split(t_str *strr, t_list **head, int flag)
{
	if (strr->join)
		ft_lstnew_back(head, strr->join, 0);
	if (strr->str[strr->i + 1] || strr->str[strr->i] == strr->c)
	{
		if (strr->str[strr->i] != ' ')
			strr->join = ft_new_strjoin(NULL, strr->str[strr->i]);
		if (strr->str[strr->i + 1] == strr->c && strr->c != ' ')
		{
			strr->i = strr->i + 1;
			strr->join = ft_strjoin(strr->join, strr->join);
		}
		if (strr->str[strr->i] != ' ')
			ft_lstnew_back(head, strr->join, flag);
	}
	strr->join = NULL;
	strr->flag = 0;
}

t_list	*split_end_or(char *line, char *set, int check)
{
	t_list		*head;
	t_quotes	qutes;
	t_str		strr;
	int			ff;

	head = NULL;
	ini_str(&strr);
	initialize(&qutes, NULL);
	strr.str = line;
	ff = 4;
	if (!strcmp(set, "<> "))
		ff = 2;
	while (line[strr.i])
	{
		ft_check_quotes(line[strr.i], &qutes);
		charset(line[strr.i], set, &strr);
		if (line[strr.i] == strr.c && (line[strr.i + 1] == strr.c || check == 0)
			&& !qutes.cp && !qutes.cq && !qutes.cs)
			strr.flag = 1;
		else
			strr.join = ft_new_strjoin(strr.join, line[strr.i]);
		if (strr.flag == 1 || !line[strr.i + 1])
			utils_split(&strr, &head, ff);
		strr.i++;
	}
	return (head);
}

void	ft_print_error(char *cmd, char *str)
{
	int	ex;

	ex = 126;
	if (errno == 2)
		ex = 127;
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : ", 2);
	if (!ft_strrchr(cmd, '/'))
	{
		str = "command not found";
		ex = 127;
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(ex);
}

char	*ft_new_strjoin(char *str, char c)
{
	int		i;
	char	*join;

	join = malloc(ft_strlen(str) + 2);
	ft_lstadd_back(&(global->head_free), ft_lstnew_v1(join));
	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			join[i] = str[i];
			i++;
		}
	}
	if (c == 0)
		join[i] = c;
	else
	{
		join[i] = c;
		i++;
		join[i] = 0;
	}
	return (join);
}
