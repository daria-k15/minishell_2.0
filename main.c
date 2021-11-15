/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:40:33 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/15 17:04:29 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shlvl(t_env *env_list)
{
	t_env	*current;
	int		shlvl;

	current = env_exists(env_list, "SHLVL");
	if (current)
	{
		if (current->value)
		{
			shlvl = ft_atoi(current->value);
			free(current->value);
		}
		if (!current->value || shlvl < 0)
			shlvl = 0;
		shlvl++;
		current->value = ft_itoa(shlvl);
	}
	else
		change_envlist("SHLVL=1", env_list);
}

static t_ctrl	*ctrl_init(char **envp, int ac, char **av)
{
	t_ctrl	*control;
	t_env	*oldpwd;

	(void)ac;
	(void)av;
	control = (t_ctrl *)malloc(sizeof(t_ctrl));
	control->env_list = env_init(envp);
	control->fd_in = dup(STDIN_FILENO);
	control->fd_out = dup(STDOUT_FILENO);
	control->pid = 1;
	control->print = 0;
	shlvl(&(control->env_list));
	oldpwd = env_exists(&(control->env_list), "OLDPWD");
	if (oldpwd)
		delete_env(oldpwd, &(control->env_list));
	if (ft_strequal(av[1], "-print"))
		control->print = 1;
	return (control);
}

static int	clear_in_the_end(t_ctrl *control)
{
	rl_clear_history();
	ctrl_free(control);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**array;
	t_ctrl	*control;

	control = ctrl_init(env, ac, av);
	while (1)
	{
		sighandler();
		line = readline("Z&D_Shell: ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		array = parsing(line, env);
		if (!array || !array[0])
			continue ;
		tree(array, control, env);
	}
	return (clear_in_the_end(control));
}
