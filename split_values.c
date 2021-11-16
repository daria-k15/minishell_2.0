/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:47:09 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 21:55:42 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_data	*ast_data_init(void)
{
	t_ast_data	*val;

	val = malloc(sizeof(t_ast_data));
	if (!val)
		return (NULL);
	val->file = NULL;
	val->in = 0;
	val->out = 1;
	val->pipe = NULL;
	return (val);
}

char	*tree_single_quote(char *line, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	if (check_char(line, '\'', j + 1) == 1)
	{
		while (line[++(*i)])
		{
			if (line[*i] == '\'')
				break ;
		}
		tmp = ft_substr(line, 0, j);
		tmp2 = ft_substr(line, j + 1, *i - j - 1);
		tmp = ft_strjoin(tmp, tmp2);
		tmp3 = ft_strdup(line + *i + 1);
		tmp3 = ft_strjoin(tmp, tmp3);
		return (tmp3);
	}
	else
	{
		write(2, "Syntax error!\n", ft_strlen("Syntax error!\n"));
		return (NULL);
	}
}

char	*tree_skip_space(char *line, int *i)
{
	int	j;

	j = *i;
	while (line[j] == ' ')
		j++;
	line = ft_substr(line, j, ft_strlen(line));
	return (line);
}

char	**split_values2(char *line, char **env, char **array)
{
	char	*tmp;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
			line = tree_single_quote(line, &i);
		if (line[i] == '\"')
			line = tree_double_quote(line, &i, env);
		if (line[i] == '$')
			line = parse_dollar(line, &i, env);
		if (line[i] == ' ')
		{
			tmp = ft_substr(line, 0, i);
			line = tree_skip_space(line, &i);
			array = add_val(array, tmp);
			i = -1;
		}
	}
	array = add_val(array, line);
	// free_array(env);
	return (array);
}

char	**split_values(char *line, char **env)
{
	char	**array;
	int		i;
	char	*tmp;

	i = -1;
	array = (char **)malloc(sizeof(char *));
	if (!array)
		return (0);
	array[0] = NULL;
	return (split_values2(line, env, array));
}
