/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 20:55:34 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 20:58:43 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_env(char const *s, char c)
{
	char	**str_array;
	int		i;

	i = 0;
	str_array = (char **)malloc(sizeof(char *) * 3);
	if (str_array == NULL)
		return (NULL);
	while (s[i] && s[i] != c)
		i++;
	str_array[0] = ft_substr(s, 0, i);
	if (i + 1 < (int)ft_strlen(s))
	{
		i++;
		str_array[1] = ft_substr(s, i, ft_strlen(s) - i);
	}
	else
		str_array[1] = ft_strdup("");
	str_array[2] = NULL;
	return (str_array);
}

void	print_export_list(t_env *start, int fdout)
{
	t_env	*temp;

	temp = start;
	while (temp != NULL)
	{
		if (!ft_strequal(temp->key, "_"))
		{
			ft_putstr_fd("declare -x ", fdout);
			ft_putstr_fd(temp->key, fdout);
			if (temp->value)
			{
				ft_putchar_fd('=', fdout);
				ft_putchar_fd('"', fdout);
				ft_putstr_fd(temp->value, fdout);
				ft_putchar_fd('"', fdout);
			}
			ft_putchar_fd('\n', fdout);
		}
		temp = temp->next;
	}
}

void	ft_swap(t_env **start, t_env *a, t_env *b)
{
	t_env	*temp;
	t_env	*temp2;

	temp = NULL;
	temp2 = NULL;
	if (!a || !b || !start)
		return ;
	if (ft_strncmp((*start)->key, a->key, ft_strlen(a->key)) != 0)
	{
		temp = (*start);
		while (ft_strncmp(temp->next->key, a->key, ft_strlen(a->key)))
			temp = temp->next;
		temp->next = b;
		temp2 = b->next;
		b->next = a;
		a->next = temp2;
	}
	else
	{
		(*start) = b;
		a->next = b->next;
		(*start)->next = a;
	}
}

t_env	*ft_lastnode(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	env_node_create(t_env **lst, char **d)
{
	t_env	*new;

	if (!d || !lst)
		return (1);
	new = (t_env *)malloc(sizeof(t_env));
	if (!d || !new)
		return (1);
	new->key = d[0];
	new->value = d[1];
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
		ft_lastnode(*lst)->next = new;
	return (0);
}
