/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 12:28:52 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 17:16:35 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bubble_sort(t_env **start)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;
	int		len;

	if ((*start) == NULL)
		return ;
	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = (*start);
		while (ptr1->next != lptr)
		{
			len = ft_strlen(ptr1->key);
			swapped = ft_strncmp(ptr1->key, ptr1->next->key, len);
			if (swapped > 0)
				ft_swap(&(*start), ptr1, ptr1->next);
			else
				ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

static void	export_add_env(char **cmd_array, t_env **env_list)
{
	int	i;

	i = -1;
	while (cmd_array[++i])
	{
		if (export_pair_isok(cmd_array[i]))
			change_envlist(cmd_array[i], env_list);
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(cmd_array[i], STDERR_FILENO);
			ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
			set_exit(1);
		}
	}
}

void	export_builtin(char **cmd_array, t_env **env_list, int fdout)
{
	t_env	*export_list;

	export_list = NULL;
	if (ft_arraylen(cmd_array) == 1)
	{
		export_list = env_cpy(*env_list);
		bubble_sort(&export_list);
		print_export_list(export_list, fdout);
		free_env(export_list);
	}
	else
		export_add_env(cmd_array, env_list);
	free_array(cmd_array);
	set_exit(0);
}
