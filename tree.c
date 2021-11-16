/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <heveline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:58:44 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/17 02:10:20 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ast_data_free(t_ast_data *val)
{
	ast_data_default(val);
	free(val);
}

void	go_through_nodes(t_ast *ast, t_ctrl *c, t_ast_data *val, char **envp)
{
	if (!ast)
	{
		if (c->pid == 0)
		{
			ctrl_free(c);
			ast_data_free(val);
			tree_free(&ast);
			exit(0);
		}
		else
			return ;
	}
	else if (!ft_strcmp((char *)ast->value, ">")
		|| !ft_strcmp((char *)ast->value, ">>"))
		right_redir(ast, c, val, envp);
	else if (ft_strcmp((char *)ast->value, "<") == 0
		|| ft_strequal((char *)ast->value, "<<"))
		left_redir(ast, c, val, envp);
	else if (ft_strcmp(ast->value, "|") == 0)
		pipe_func(ast, c, val, envp);
	else
		cmd_commands(ast, c, val, envp);
}

void	tree_handle(t_ast *ast, t_ctrl *control, char **envp)
{
	pid_t		pid;
	int			status;
	t_ast_data	*val;

	if (check_heredoc(ast))
	{
		pid = fork();
		signal(SIGINT, SIG_IGN);
		if (pid == 0)
		{
			tree_sighandler();
			heredoc_func(ast, control);
			exit(0);
		}
		waitpid(pid, &status, 0);
		if (WTERMSIG(status) == SIGINT)
			exit(1);
	}
	val = ast_data_init();
	go_through_nodes(ast, control, val, envp);
	ast_data_free(val);
}

void	tree_free(t_ast **tree)
{
	// if (*tree)
	// {
		if ((*tree)->left != NULL)
			tree_free(&(*tree)->left);
		if ((*tree)->right != NULL)
			tree_free(&(*tree)->right);
		free((*tree)->value);
		// if ((*tree)->value)
		free((*tree));
	// }
	(*tree) = NULL;
}

void	tree(char **array, t_ctrl *control, char **envp)
{
	t_ast	*ast;

	ast = NULL;
	ast = tree_create(ast, array);
	tree_handle(ast, control, envp);
	if (control->print == 1)
		tree_print_rec(ast, 0);
	tree_free(&ast);
}
