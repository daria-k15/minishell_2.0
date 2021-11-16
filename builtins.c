/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:39:39 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 20:52:33 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(char **cmd_array, t_env *start, int fdout)
{
	t_env	*temp;

	temp = start;
	while (temp != NULL)
	{
		if (temp->value)
		{
			ft_putstr_fd(temp->key, fdout);
			ft_putchar_fd('=', fdout);
			ft_putstr_fd(temp->value, fdout);
			ft_putchar_fd('\n', fdout);
		}
		temp = temp->next;
	}
	free_array(cmd_array);
	set_exit(0);
}

void	echo_builtin_2(char **cmd_array, int fdout, int *i, int endl)
{
	if (ft_strcmp(cmd_array[*i], "$?") == 0)
		ft_putnbr_fd(get_exit(), fdout);
	else
	{
		while (cmd_array[*i])
		{
			ft_putstr_fd(cmd_array[*i], fdout);
			if (cmd_array[*i + 1])
				ft_putstr_fd(" ", fdout);
			(*i)++;
		}
	}
	if (endl != 1)
		ft_putstr_fd("\n", fdout);
	free_array(cmd_array);
	set_exit(0);
}

void	echo_builtin(char **cmd_array, int fdout)
{
	int	endl;
	int	i;

	endl = 0;
	i = 1;
	if (ft_arraylen(cmd_array) == 1)
	{
		ft_putendl_fd("", fdout);
		return ;
	}
	if (cmd_array[1] && ft_strequal(cmd_array[1], "-n"))
	{
		endl = 1;
		while (cmd_array[i] && ft_strequal(cmd_array[i], "-n"))
			i++;
	}
	echo_builtin_2(cmd_array, fdout, &i, endl);
}

void	pwd_builtin(char **cmd_array, int fdout)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, fdout);
	free(pwd);
	free_array(cmd_array);
	set_exit(0);
}

void	unset_builtin(char **cmd_array, t_env **env_list, int fdout)
{
	t_env	*deleted;
	int		i;

	i = 1;
	while (cmd_array[i])
	{
		if (unset_arg_isok(cmd_array[i]))
		{
			deleted = env_exists(env_list, cmd_array[i]);
			if (deleted)
				delete_env(deleted, env_list);
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(cmd_array[i], STDERR_FILENO);
			ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
			set_exit(1);
		}
		i++;
	}
	free_array(cmd_array);
	set_exit(0);
}
