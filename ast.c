/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:06:20 by heveline          #+#    #+#             */
/*   Updated: 2021/11/16 21:14:57 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*tree_create(t_ast *ast, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ast == NULL)
			ast = node_create(array[i]);
		else
			ast = add_value(&ast, array[i]);
		i++;
	}
	return (ast);
}

t_ast	*node_create(char *value)
{
	t_ast	*node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (node != NULL)
	{
		node->left = NULL;
		node->right = NULL;
		node->value = value;
		if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
			node->prior = 3;
		else if (ft_strcmp(value, ">>") == 0 || ft_strcmp(value, "<<") == 0)
			node->prior = 3;
		else if (ft_strcmp(value, "|") == 0)
			node->prior = 2;
		else
			node->prior = 0;
	}
	return (node);
}

t_ast	*firstnode(t_ast **ast, t_ast *new, t_ast *tmp, char *value)
{
	int		prior;

	prior = return_prior(value);
	if (prior == 2 || prior == 3)
		return (fnode(ast, new, tmp, value));
	if ((*ast)->prior == 3)
	{
		while (tmp->left != NULL && return_prior(tmp->left->value) == 3)
			tmp = tmp->left;
		if (tmp->right == NULL)
			tmp->right = new;
		else
			tmp->left = new;
		return (*ast);
	}
	while (tmp->left != NULL)
		tmp = tmp->left;
	tmp->left = new;
	return (*ast);
}

t_ast	*add_value(t_ast **ast, char *value)
{
	t_ast	*tmp;
	t_ast	*new;
	t_ast	*tmp3;
	int		prior;

	new = node_create(value);
	tmp = *ast;
	prior = return_prior(value);
	if ((*ast)->prior == 2)
	{
		while (tmp->right != NULL)
		{
			if ((ft_strcmp(value, "|") == 0 || return_prior(value) == 3)
				&& ft_strcmp(tmp->right->value, "|") != 0)
				return (addnode(ast, new, tmp, value));
			if (return_prior(tmp->value) == 3)
				return (addtoend(ast, new, tmp));
			tmp = tmp->right;
		}
		tmp->right = new;
		return (*ast);
	}
	return (firstnode(ast, new, tmp, value));
}
