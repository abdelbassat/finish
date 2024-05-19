/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:16 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/17 21:14:26 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_remove_if_v2(t_list **head, char *target) // hena can not cause leaks
{
	t_list *prev;
	t_list *new_node;
	t_list *temp;

	if (!*head || !head)
		return ;
	temp = *head;
	prev = NULL;
	new_node = NULL;
	while (temp)
	{
		if (strcmp((char *)temp->key, target) == 0)
		{
			if (prev)
			{
				prev->next = temp->next;
				new_node = temp->next;
				temp = new_node;
			}
			else
			{
				*head = temp->next;
				temp = *head;
			}
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}

t_list	*ft_remove_if_v1(t_list **head, char *target)
{
	t_list	*temp;

	if (!*head || !head)
		return (NULL);
	temp = *head;
	while (temp)
	{
		if (strcmp((char *)temp->key, target) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
void	ft_print_list(void)
{
	t_list	*head;
	t_list	*save;

	head = global->data->env_list;
	save = ft_remove_if_v1(&head, "_");
	ft_remove_if_v2(&head, "_");
	ft_lstadd_back(&head, ft_lstnew((char *)save->content));
	while (head)
	{
		if (ft_strchr_edit((char *)head->content, '=') == 1)
			printf("%s\n", (char *)head->content);
		head = head->next;
	}
}
int	ft_env_size(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}
void	ft_buffer_to_list(t_list **head, char **command)
{
	int		i;
	char	*join;
	char	*buff;

	i = 0;
	if (ft_env_size(command) != 0)
	{
		while (command[i])
		{
			ft_lstadd_back(head, ft_lstnew(command[i]));
			i++;
		}
	}
	else
	{
		buff = malloc(100);
		ft_lstadd_back(head, ft_lstnew(getcwd(buff, 100)));
		join = ft_strjoin("SHLVL=", ft_itoa(global->shell));
		ft_lstadd_back(head, ft_lstnew(join));
		ft_lstadd_back(head,
			ft_lstnew("PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/home/mmad/.local/bin/:/home/mmad/.local/bin/"));
		ft_lstadd_back(head, ft_lstnew("_=/usr/bin/env"));
	}
}
void	ft_buffer_to_list_v1(t_list **head, t_list *command)
{
	while (command)
	{
		ft_lstadd_back(head, ft_lstnew(command->content));
		command = command->next;
	}
}
int	ft_if_plus_eql(char *str) // hena can not cause leaks
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_if_exist_var(t_list *env, t_list *head) // hena can not cause leaks
{
	t_list *temp_node;
	t_list *temp_env;

	temp_node = head;
	temp_env = env;
	if (temp_node->key && temp_node->value)
	{
		while (temp_env)
		{
			while (temp_node)
			{
				if (strcmp(temp_env->key, temp_node->key) == 0
					&& strcmp(temp_env->value, temp_node->value) != 0
					&& ft_if_plus_eql(temp_node->content) == 0)
				{
					temp_env->content = ft_strdup(temp_node->content);
					temp_env->value = ft_strdup(temp_node->value);
				}
				else if (ft_if_plus_eql(temp_node->content) == 1
					&& strcmp(temp_env->key, temp_node->key) == 0)
					temp_env->value = strcat(temp_env->value, temp_node->value);
				temp_node = temp_node->next;
			}
			temp_node = head;
			temp_env = temp_env->next;
		}
		temp_node = head;
		temp_env = env;
	}
}

int	ft_found_equal(char *str) // hena can not cause leaks
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		else if (str[i] == '+' && str[i + 1] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strchr_i(const char *s) // hena can not cause leaks
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] && s[i + 1] == '=')
		{
			i += 2;
			return ((char *)&s[i]);
		}
		else if ((s[i] == '+' || (s[i + 1] && s[i + 1] == '=')))
		{
			i += 2;
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == '=' || (s[i + 1] && s[i + 1] == '='))
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_strchr_edit(const char *s, int c)
// same function exit | hena can not cause leaks
{
	size_t i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	if (s[i] == (char)c)
		return (1);
	return (0);
}

void	ft_link_node(t_list *head) // hena can not cause leaks
{
	t_list *temp;

	temp = head;
	while (temp)
	{
		if (ft_strchr_edit(temp->content, '=') == 1
			|| ft_strchr_edit(temp->content, '+') == 1)
		{
			temp->key = ft_substr(temp->content, 0,
					ft_found_equal(temp->content));
			if (ft_strchr_edit(temp->key, '+') == 1)
				printf("bash: export: `%s': not a valid identifier\n",
					temp->content);
			temp->value = ft_strchr_i(temp->content);
		}
		else
		{
			temp->key = ft_substr(temp->content, 0, ft_strlen(temp->content));
			temp->value = ft_strdup("");
		}
		temp = temp->next;
	}
	temp = head;
}

void	ft_remove_if(t_list **head, char *target) // hena can not cause leaks
{
	t_list *temp;
	t_list *prev;
	t_list *new_node;

	if (!*head || !head)
		return ;
	temp = *head;
	prev = NULL;
	new_node = NULL;
	while (temp)
	{
		if (strcmp((char *)temp->key, target) == 0)
		{
			if (strcmp(target, "_") == 0)
				return ;
			if (prev)
			{
				prev->next = temp->next;
				new_node = temp->next;
				temp = new_node;
			}
			else
			{
				*head = temp->next;
				temp = *head;
			}
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}

int	ft_search_if_key_exist(t_list **env, t_list *head)
// hena can not cause leaks
{
	t_list *temp_env;

	if (!head || !head->key || !head->value || !env || !(*env))
		return (0);
	temp_env = *env;
	if (temp_env->key && temp_env->value)
	{
		while (temp_env)
		{
			if (strcmp((char *)temp_env->key, (char *)head->key) == 0)
				return (0);
			temp_env = temp_env->next;
		}
	}
	temp_env = *env;
	return (1);
}

t_list	*ft_fill_out(t_list **env_list, t_list *head)
{
	t_list	*temp;
	t_list	*result;
	t_list	*temp_env_list;

	temp_env_list = *env_list;
	if (!head)
		return (NULL);
	temp = head;
	ft_link_node(temp);
	while (temp != NULL)
	{
		if (ft_search_if_key_exist(&temp_env_list, temp) == 1)
		{
			result = temp;
			result = ft_create_var(temp->content, '+');
			// printf("%p\n" , result);
			ft_lstadd_back(env_list, ft_lstnew(result->content));
			ft_link_node(*env_list);
		}
		temp_env_list = (*env_list);
		temp = temp->next;
	}
	temp = head;
	return (*env_list);
}
