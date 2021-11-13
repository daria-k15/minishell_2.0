/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingAstArray3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:19:20 by heveline          #+#    #+#             */
/*   Updated: 2021/11/12 20:19:24 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_line(char *line, int *i)
{
	if (line[(*i) + 1] == '>' || line[(*i) + 1] == '<')
		line = ft_strdup(line + *i + 2);
	else if (line[(*i)] == '>' || line[(*i)] == '<' || line[(*i)] == '|')
		line = ft_strdup(line + *i + 1);
	return (line);
}

char	**pars_to_array(char *line, char **array, char **envp, int *i)
{
	char	*tmp;

	while (line[++(*i)])
	{
		if (line[(*i)] == '>' || line[(*i)] == '<' || line[(*i)] == '|')
		{
			line = redirect_parse(line, i);
			tmp = ft_substr(line, 0, find_redir(line));
			array = add_val(array, tmp);
			line = ft_substr(line, find_redir(line),
					ft_strlen(line) - find_redir(line));
			*i = 0;
			if (line[(*i) + 1] == '>' || line[(*i) + 1] == '<')
				array = add_val(array, ft_substr(line, 0, *i + 2));
			else if (line[(*i)] == '>' || line[(*i)] == '<'
				|| line[(*i)] == '|')
				array = add_val(array, ft_substr(line, 0, *i + 1));
			line = new_line(line, i);
			*i = -1;
		}
	}
	line = parsing2(line);
	array = add_val(array, line);
	return (array);
}

char	**parsing(char *line, char **envp)
{
	int		i;
	char	**array;

	i = -1;
	array = (char **)malloc(sizeof(char *));
	if (!array)
		return (NULL);
	array[0] = NULL;
	array = pars_to_array(line, array, envp, &i);
	return (array);
}
