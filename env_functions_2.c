/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:58:13 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 21:01:13 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envlist_init(char **env)
{
	t_env	*start;
	int		n;
	size_t	a;
	char	**d;

	n = 0;
	a = 0;
	start = NULL;
	while (a < ft_arraylen(env) && !n)
	{
		d = ft_split_env(env[a++], '=');
		n = env_node_create(&start, d);
	}
	return (start);
}

t_env	*env_cpy(t_env *head)
{
	t_env	*newnode;

	newnode = NULL;
	if (head == NULL)
		return (NULL);
	else
	{
		newnode = (t_env *)malloc(sizeof(t_env));
		newnode->key = head->key;
		newnode->value = head->value;
		newnode->next = env_cpy(head->next);
		return (newnode);
	}
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	if (head)
	{
		tmp = head;
		free_env(head->next);
		free(tmp);
		tmp = NULL;
	}
}

int	unset_arg_isok(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
		if ((arg[i] != '_' && !ft_isalnum(arg[i++])) || ft_isdigit(arg[0]))
			return (0);
	return (1);
}

int	export_pair_isok(char *pair)
{
	int	i;

	i = 0;
	while (pair[i])
	{
		if (i == 0 && (ft_isdigit(pair[i]) || pair[i] == '=' || pair[i] == '+'))
			return (0);
		if ((pair[i] == '+' && pair[i + 1] && pair[i + 1] == '=')
			|| pair[i] == '=')
			return (1);
		if (pair[i] != '_' && !ft_isalnum(pair[i]))
			return (0);
		i++;
	}
	return (1);
}
