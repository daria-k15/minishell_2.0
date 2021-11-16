/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:00:41 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 21:13:57 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_exists(t_env **env_list, char *key)
{
	t_env	*temp;

	temp = *env_list;
	while (temp)
	{
		if (ft_strequal(temp->key, key))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	change_envlist_2(t_env **env_list, char **temp, int tobejoined)
{
	t_env	*current;
	char	*tempvalue;

	current = env_exists(env_list, temp[0]);
	if (current)
	{
		tempvalue = current->value;
		if (tobejoined)
			current->value = ft_strjoin(current->value, temp[1]);
		else
			current->value = temp[1];
		free(tempvalue);
	}
	else
		env_node_create(env_list, temp);
}

void	change_envlist(char *new_env, t_env **env_list)
{
	char	**temp;
	char	*temp2;
	int		tobejoined;

	tobejoined = 0;
	temp = ft_split_env(new_env, '=');
	if (temp[0][ft_strlen(temp[0]) - 1] == '+')
	{
		temp2 = temp[0];
		temp[0] = ft_substr(temp[0], 0, ft_strlen(temp[0]) - 1);
		free(temp2);
		tobejoined++;
	}
	change_envlist_2(env_list, temp, tobejoined);
}

void	delete_env(t_env *deleted, t_env **env_list)
{
	t_env	*ptr1;

	ptr1 = (*env_list);
	while (!ft_strequal(ptr1->next->key, deleted->key))
		ptr1 = ptr1->next;
	ptr1->next = deleted->next;
	free(deleted->key);
	free(deleted->value);
	free(deleted);
}

char	**env_to_array(t_env **env_list)
{
	int		i;
	t_env	*tmp;
	char	**array;
	char	*equal;

	i = 0;
	tmp = *env_list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	array = love_norme(array, i);
	tmp = *env_list;
	i = 0;
	while (tmp)
	{
		equal = ft_strjoin(tmp->key, "=");
		array[i++] = ft_strjoin(equal, tmp->value);
		tmp = tmp->next;
		free(equal);
	}
	array[i] = NULL;
	return (array);
}
