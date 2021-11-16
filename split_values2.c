/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_values2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:55:21 by heveline          #+#    #+#             */
/*   Updated: 2021/11/16 22:55:23 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tree_double_quote2(char *line, int *i, char **envp, int j)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j + 1, *i - j - 1);
	tmp3 = ft_strdup(line + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	return (tmp);
}

char	*tree_double_quote(char *line, int *i, char **envp)
{
	int		j;

	j = *i;
	if (check_char(line, '\"', j + 1) == 1)
	{
		while (line[++(*i)])
		{
			if (line[*i] == '\\' && (line[*i + 1] == '\"'
					|| line[*i + 1] == '$' || line[*i + 1] == '\\'))
				line = slash_parse(line, i);
			if (line[*i] == '$')
				line = parse_dollar(line, i, envp);
			if (line[*i] == '\"')
				break ;
		}
		(*i)--;
		return (tree_double_quote2(line, &i, envp, j));
	}
	else
	{
		write(2, "Syntax error!\n", ft_strlen("Syntax error!\n"));
		exit(1);
	}
}
