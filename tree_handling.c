/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <heveline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:47:09 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/17 02:03:24 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_node(t_ast *ast, t_ctrl *data, t_ast_data *val)
{
	ast_data_free(val);
	ctrl_free(data);
	// tree_free(&ast);
}

char	**cmd_commands2(t_ast *ast, t_ctrl *control, t_ast_data *val)
{
	char	**cmd_array;
	char	**env;

	env = env_to_array(&(control->env_list));
	cmd_array = split_values(ast->value, env);
	free_array(env);
	if (cmd_array[0] == NULL)
	{
		free(cmd_array);
		clean_node(ast, control, val);
		exit(0);
	}
	return (cmd_array);
}

void	cmd_commands(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp)
{
	char	**cmd_array;

	cmd_array = cmd_commands2(ast, control, val);
	if (ft_strcmp(cmd_array[0], "env") == 0)
		env_builtin(cmd_array, control->env_list, val->out);
	else if (ft_strcmp(cmd_array[0], "export") == 0)
		export_builtin(cmd_array, &(control->env_list), val->out);
	else if (ft_strcmp(cmd_array[0], "unset") == 0)
		unset_builtin(cmd_array, &(control->env_list), val->out);
	else if (ft_strcmp(cmd_array[0], "echo") == 0)
		echo_builtin(cmd_array, val->out);
	else if (ft_strcmp(cmd_array[0], "cd") == 0)
		cd_builtin(cmd_array, &(control->env_list));
	else if (ft_strcmp(cmd_array[0], "exit") == 0)
		exit_builtin(cmd_array, control, val->out);
	else if (ft_strcmp(cmd_array[0], "pwd") == 0)
		pwd_builtin(cmd_array, val->out);
	else if (ft_strcmp(cmd_array[0], "") == 0)
		return ;
	else
		binary_command(ast, cmd_array, control, val);
	if (!control->pid)
		exit(get_exit());
}

void	ctrl_free(t_ctrl *control)
{
	free_env(control->env_list);
	free(control->mininame);
	free(control);
}

void	ast_data_default(t_ast_data *val)
{
	int	i;

	if (val->file)
	{
		i = 0;
		while (val->file[i] != -1)
			close(val->file[i++]);
		free(val->file);
		val->file = NULL;
	}
	val->in = 0;
	val->out = 1;
}
