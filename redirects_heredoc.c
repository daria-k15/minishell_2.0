/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:47:39 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 21:57:32 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_her(char *str, int fd)
{
	rl_redisplay();
	ft_putendl_fd(str, fd);
	free(str);
}

static void	write_to_tmp(t_ast *ast, int fd)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (ft_strequal(buf, ast->value))
			break;
		if (buf)
			print_her(buf, fd);
	}
	free(buf);
}

void	heredoc_func(t_ast *ast, t_ctrl *control)
{
	int	i;

	if (!ast)
		return;
	if (ft_strequal(ast->value, "<<"))
	{
		i = open("/tmp/.tmp_heredoc", O_CREAT | O_TRUNC | O_WRONLY,
				 S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
		write_to_tmp(ast->right, i);
		close(i);
	}
	heredoc_func(ast->left, control);
	heredoc_func(ast->right, control);
}

void create_files(t_ast_data *val, int fd)
{
	int *tmp;
	int i;

	i = 0;
	if (val->file)
	{
		while (val->file[i] != -1)
			i++;
	}
	tmp = malloc(sizeof(int) * (i + 2));
	if (i != 0)
	{
		i = 0;
		while (val->file[i] != -1)
		{
			tmp[i] = val->file[i];
			i++;
		}
		free(val->file);
	}
	tmp[i++] = fd;
	tmp[i] = -1;
	val->file = tmp;
}
