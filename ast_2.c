/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:26:09 by heveline          #+#    #+#             */
/*   Updated: 2021/11/16 16:26:19 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	return_prior(char *value)
{
	if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
		return (3);
	else if (ft_strcmp(value, ">>") == 0 || ft_strcmp(value, "<<") == 0)
		return (3);
	else if (ft_strcmp(value, "|") == 0)
		return (2);
	return (0);
}

t_ast	*addtoend(t_ast **ast, t_ast *new, t_ast *tmp)
{
	while (tmp->left != NULL && return_prior(tmp->left->value) == 3)
		tmp = tmp->left;
	if (tmp->right == NULL)
		tmp->right = new;
	else
		tmp->left = new;
	return (*ast);
}

t_ast	*addnode(t_ast **ast, t_ast *new, t_ast *tmp, char *value)
{
	if (return_prior(tmp->right->value) != 3 || return_prior(value) == 2)
	{
		new->left = tmp->right;
		tmp->right = new;
		return (*ast);
	}
	else
	{
		while (tmp->right != NULL && ft_strcmp(tmp->right->value, "|") == 0)
			tmp = tmp->right;
		while (tmp->right != NULL && return_prior(tmp->right->value) == 3)
			tmp = tmp->right;
		while (tmp->left != NULL && return_prior(tmp->left->value) == 3)
			tmp = tmp->left;
		new->left = tmp->left;
		tmp->left = new;
		return (*ast);
	}
}

t_ast	*fnode(t_ast **ast, t_ast *new, t_ast *tmp, char *value)
{
	if (return_prior((*ast)->value) != 3 || ft_strcmp(value, "|") == 0)
	{
		new->left = *ast;
		return (new);
	}
	else
	{
		while (tmp->left != NULL && return_prior(tmp->left->value) == 3)
			tmp = tmp->left;
		new->left = tmp->left;
		tmp->left = new;
		return (*ast);
	}
}
