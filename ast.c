/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:06:20 by heveline          #+#    #+#             */
/*   Updated: 2021/11/12 16:06:22 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*create_tree(t_ast *ast, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ast == NULL)
			ast = create_node(array[i]);
		else
			add_value(&ast, array[i]);
		i++;
	}
	return (ast);
}

t_ast	*create_node(char *value)
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

void	insert_left(t_ast **ast, char *value)
{
	t_ast	*tmp;

	tmp = NULL;
	if (&((*ast)->left) != NULL)
		insert_left(&(*ast)->left, value);
	if (!(*ast))
	{
		tmp = (t_ast *)malloc(sizeof(t_ast));
		tmp->value = value;
		tmp->left = NULL;
		tmp->right = NULL;
		if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
			tmp->prior = 3;
		else if (ft_strcmp(value, "|") == 0)
			tmp->prior = 2;
		else if (check_arg(value))
			tmp->prior = 1;
		else
		{
			tmp->prior = 0;
		}
		(*ast) = tmp;
	}
}

int	return_prior(char *value)
{
	if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0)
		return (3);
	else if (ft_strcmp(value, ">>") == 0 || ft_strcmp(value, "<<") == 0)
		return (3);
	else if (ft_strcmp(value, "|") == 0)
		return (2);
	else if (check_arg(value))
		return (1);
	return (0);
}

void	add_value(t_ast **ast, char *value)
{
	t_ast	*tmp;
	int		prior;

	prior = return_prior(value);
	if ((*ast)->prior == 3 && prior == 0)
		(*ast)->right = create_node(value);
	else if ((*ast)->prior == 3 && prior == 2)
	{
		tmp = create_node(value);
		tmp->left = *ast;
		*ast = tmp;
	}
	else if ((*ast)->prior == 2 && prior == 0)
		(*ast)->right = create_node(value);
	else if ((*ast)->prior > prior)
		insert_left(&(*ast)->left, value);
	else
	{
		tmp = create_node(value);
		tmp->left = *ast;
		*ast = tmp;
	}
}
