/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printAst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:07:44 by heveline          #+#    #+#             */
/*   Updated: 2021/11/13 09:39:27 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printtabs(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("\t");
		i++;
	}
}

void	tree_print_rec(t_ast *ast, int level)
{
	if (ast == NULL)
	{
		printtabs(level);
		printf("-----<empty>-----\n");
		return ;
	}
	printtabs(level);
	printf("value = |%s| prior = |%d|\n ", ast->value, ast->prior);
	printtabs(level);
	printf("left\n");
	tree_print_rec(ast->left, level + 1);
	printtabs(level);
	printf("right\n");
	tree_print_rec(ast->right, level + 1);
	printtabs(level);
	printf("done\n");
}
