/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:35:45 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 18:07:09 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_handler(char *cmd, char **env)
{
	int		i;
	char	**path_list;
	char	*temp;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		ft_err("Error: problem with ENV, no PATHs found");
	path_list = ft_split(env[i] + 5, ':');
	i = 0;
	while (path_list[i])
	{
		path_list[i] = ft_strjoin(path_list[i], "/");
		temp = ft_strjoin(path_list[i], cmd);
		if (access(temp, F_OK) == 0)
			return (temp);
		i++;
	}
	ft_err("Error: no binary found for the command");
	return (NULL);
}

static void	execute_cmd(t_ast *ast, char **array, t_ctrl *ctrl, t_ast_data *val)
{
	char	**env;
	char	*path;

	if (dup2(val->out, STDOUT_FILENO) < 0)
		ft_err("error in dup");
	if (dup2(val->in, STDIN_FILENO) < 0)
		ft_err("error in dup");
	tree_free(&ast);
	ast_data_free(val);
	env = env_to_array(&(ctrl->env_list));
	path = path_handler(array[0], env);
	if (execve(path, array, env) == -1)
	{
		free(path);
		free_array(env);
		ft_err("Error: command not executable");
	}
}

void	binary_command(t_ast *ast, char **array, t_ctrl *ctrl, t_ast_data *val)
{
	pid_t	pid;
	int		i;

	pid = 1;
	if (ctrl->pid != 0)
		pid = fork();
	if (pid < 0)
	{
		ft_putendl_fd("Fork error", STDERR_FILENO);
		set_exit(228);
	}
	if (pid == 0 || ctrl->pid == 0)
		execute_cmd(ast, array, ctrl, val);
	waitpid(pid, &i, 0);
	set_exit(i / 256);
}
