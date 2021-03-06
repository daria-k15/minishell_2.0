/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingAstArray2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <heveline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:18:49 by heveline          #+#    #+#             */
/*   Updated: 2021/11/17 02:16:57 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*redirect2(char *tmp, char *line, int *j)
{
	int	k;

	k = -1;
	while (tmp[++k])
	{
		if (tmp[k] == '\'')
			tmp = single_quote_parse(tmp, &k);
		if (tmp[k] == '\"')
			tmp = double_quote_parse(tmp, &k);
		if (tmp[k] == '\\')
			tmp = slash_parse(tmp, &k);
		if (tmp[k] == ' ')
			tmp = skip_space(tmp, &k);
	}
	line = ft_strdup(line + *j);
	line = ft_strjoin(tmp, line);
	free(tmp);
	return (line);
}

char	*redirect_parse(char *line, int *i)
{
	int		j;
	char	*tmp;
	int		l;

	j = *i;
	l = 0;
	tmp = ft_substr(line, 0, j);
	if (tmp[l] == ' ')
	{
		while (tmp[l] == ' ')
			l++;
		tmp = ft_substr(line, l, j - l);
	}
	l = 1;
	if (tmp[ft_strlen(tmp) - l] == ' ')
	{
		while (tmp[ft_strlen(tmp) - l] == ' ')
			l++;
		tmp = ft_substr(tmp, 0, ft_strlen(tmp) - l + 1);
	}
	return (redirect2(tmp, line, &j));
}

int	find_redir(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			break ;
	}
	return (i);
}

char	**add_val(char **array, char *val)
{
	int		i;
	char	**res;

	i = 0;
	while (array[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (array[i] != NULL)
	{
		res[i] = array[i];
		i++;
	}
	res[i++] = ft_strdup(val);
	res[i] = NULL;
	return (res);
}

char	*parsing2(char *line, char **envp)
{
	int	i;
	char	*tmp;

	i = 0;
	if (line[i] == ' ')
	{
		while (line[i] == ' ')
			i++;
		line = ft_substr(line, i, ft_strlen(line) - i);
		i = -1;
	}
	while (line[++i])
	{
		if (line[i] == '\'')
			line = single_quote_parse(line, &i);
		if (line[i] == '\"')
			line = double_quote_parse(line, &i);
		if (line[i] == '\\')
			line = slash_parse(line, &i);
		if (line[i] == ' ')
			line = skip_space(line, &i);
	}
	if (line[ft_strlen(line) - 1] == ' ')
	{
		tmp = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		line = tmp;
	}
	return (line);
}
