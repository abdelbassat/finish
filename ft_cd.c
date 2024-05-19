/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:20:44 by mmad              #+#    #+#             */
/*   Updated: 2024/05/19 16:25:42 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*ft_search_if_key_exist_env_home(t_list **env, char *head)
{
	t_list	*temp_env;

	if (!head || !env || !(*env))
		return (NULL);
	else if (!strcmp(head, "?"))
		return (ft_itoa(global->data->status));
	temp_env = *env;
	if (temp_env->key && temp_env->value)
	{
		while (temp_env)
		{
			if (head)
			{
				if (!strcmp(temp_env->key, head))
					return (temp_env->value);
			}
			temp_env = temp_env->next;
		}
	}
	temp_env = *env;
	return (NULL);
}

char	*ft_getenv(char *search)
{
	if (!search)
		return (ft_strdup("$"));
	ft_link_node(global->data->env_list);
	return (ft_search_if_key_exist_env_home(&(global->data->env_list), search));
}

void	ft_cd(t_list *head)
{
	char *path = malloc(sizeof(char) * 1024);
	ft_lstadd_back(&(global->head_free), ft_lstnew_v1(path));
	if (!path)
		return ;
	t_list *temp = head;
	path = getcwd(path, 1024);
	if (ft_lstsize(temp) == 2)
	{
		char *new_dir = ft_strdup(temp->next->content);
		if (chdir(new_dir))
		{
			global->data->status = 1;
			perror(ft_strjoin("minishell: cd: ", (char *)temp->next->content));
		}
	}
	else if (ft_lstsize(temp) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		global->data->status = 1;
	}
	else
	{
		if (!ft_getenv("HOME"))
			perror("");
		else
			chdir(ft_getenv("HOME"));
	}
	// error
}