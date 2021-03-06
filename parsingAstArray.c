/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingAstArray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:14:10 by heveline          #+#    #+#             */
/*   Updated: 2021/11/16 21:29:37 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char(char *line, char ch, int i)
{
	while (line[i])
	{
		if (line[i] == ch)
			return (1);
		(i)++;
	}
	return (0);
}

char	*skip_space(char *line, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	j = *i;
	while (line[j] == ' ')
		j++;
	tmp = ft_substr(line, 0, *i + 1);
	tmp1 = ft_substr(line, j, ft_strlen(line));
	tmp2 = ft_strjoin(tmp, tmp1);
	free(tmp);
	free(tmp1);
	return (tmp2);
}

char	*single_quote_parse(char *line, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (line[++(*i)])
	{
		if (line[(*i)] == '\'')
			break ;
	}
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j + 1, *i - j - 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp3 = ft_strdup(line + *i + 1);
	tmp3 = ft_strjoin(tmp, tmp3);
	free(tmp);
	free(tmp2);
	return (tmp3);
}

char	*slash_parse(char *line, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line, 0, *i);
	tmp2 = ft_strdup(line + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(line);
	++(*i);
	return (tmp);
}

char	*double_quote_parse(char *line, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (line[++(*i)])
	{
		if (line[*i] == '\\' && (line[*i + 1] == '\"'
				|| line[*i + 1] == '$' || line[*i + 1] == '\\'))
			line = slash_parse(line, i);
		if (line[*i] == '\"')
			break ;
	}
	tmp = ft_substr(line, 0, j);
	tmp2 = ft_substr(line, j + 1, *i - j - 1);
	tmp3 = ft_strdup(line + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	(*i)--;
	return (tmp);
}
