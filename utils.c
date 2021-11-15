/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:20:58 by heveline          #+#    #+#             */
/*   Updated: 2021/11/15 11:49:46 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg(char *arg)
{
	if (ft_strcmp("echo", arg) == 0 || ft_strcmp("cd", arg) == 0
		|| ft_strcmp("pwd", arg) == 0 || ft_strcmp("export", arg) == 0
		|| ft_strcmp("unset", arg) == 0 || ft_strcmp("env", arg) == 0
		|| ft_strcmp("exit", arg) == 0)
	{
		return (1);
	}
	return (0);
}

int	check_heredoc(t_ast *ast)
{
	if (ft_strcmp(ast->value, "<<") == 0)
		return (1);
	return (0);
}

int	check_redir(t_ast *ast)
{
	if (ft_strcmp(ast->value, ">") == 0 || ft_strcmp(ast->value, ">>") == 0
		|| ft_strcmp(ast->value, "<") == 0 || ft_strcmp(ast->value, "<<") == 0)
		return (1);
	return (0);
}

void	ft_err(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str[i]);
	free(str);
}

size_t	ft_arraylen(char **str)
{
	size_t	n;

	n = 0;
	while (*str++)
		n++;
	return (n);
}