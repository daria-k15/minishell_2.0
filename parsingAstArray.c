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

char *skip_space(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp1;

	while (line[j] == ' ')
		j++;
	tmp = ft_substr(line, 0, *i + 1);
	tmp1 = ft_substr(line, j, ft_strlen(line));
	tmp1 = ft_strjoin(tmp, tmp1);
	// (*i)++;
	return (tmp1);
}

char *single_quote_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	// if (check_char(line, '\'', j + 1) == 1)
	// {
		while (line[++(*i)])
		{
			if (line[(*i)] == '\'')
				break ;
		}
		tmp = ft_substr(line, 0, j);
		tmp2 = ft_substr(line, j,  *i - j + 1);
		tmp = ft_strjoin(tmp, tmp2);
		tmp3 = ft_strdup(line + *i + 1);
		tmp3 = ft_strjoin(tmp, tmp3);
		return (tmp3);
	// }
	// else{
	// 	write(2, "Syntax error!\n", ft_strlen("Syntax error!\n"));
	// 	exit(1);
	// }
	// return (line);
}

char	*slash_parse(char *line, int *i)
{
	// int j = *i;
	char *tmp;
	char *tmp2;

	tmp = ft_substr(line, 0, *i);
	tmp2 = ft_strdup(line + *i);
	tmp = ft_strjoin(tmp, tmp2);
	free(line);
	++(*i);
	return (tmp);
}

char	*double_quote_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	// if (check_char(line, '\"', j + 1) == 1)
	// {
		while (line[++(*i)])
		{
			if (line[*i] == '\\' && (line[*i + 1] == '\"' || line[*i + 1] == '$' || line[*i + 1] == '\\'))
				line = slash_parse(line, i);
			// if (line[*i] == '$')
			// 	line = parse_dollar(line, i, envp);
			if (line[*i] == '\"')
				break ;
		}
		tmp = ft_substr(line, 0, j);
		tmp2 = ft_substr(line, j,  *i -j + 1);
		tmp3 = ft_strdup(line + *i + 1);
		tmp = ft_strjoin(tmp, tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		// (*i)--;
		return (tmp);
	// }
	// else{
	// 	write(2,"Syntax error!\n", ft_strlen("Syntax error!\n"));
	// 	exit(1);
	// }
	// return (line);
}

char *redirect_parse(char *line, int *i, char **envp)
{
	int j = *i;
	int		k;
	char	*tmp;
	int		l;

	l = 0;
	k = -1;
	tmp = ft_substr(line, 0, j);
	if (tmp[l] == ' ')
	{
		while (tmp[l] == ' ')
			l++;
		tmp = ft_substr(line, l, j - l);
	}
	if (tmp[ft_strlen(tmp) - 1] == ' ')
		tmp = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	while(tmp[++k])
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
	line = ft_strdup(line + j);
	line = ft_strjoin(tmp, line);
	return (line);
}

int find_redir(char *line)
{
	int i;

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
	int i = 0;
	char **res;

	while (array[i])
		i++;
	res = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (array[i] != NULL)
	{
		res[i] = array[i];
		i++;
	}
	res[i++] = val;
	res[i] = NULL;
	return (res);	
}

char **parsing(char *line, char **envp)
{
	int		i;
	char	**array;
	char	*tmp;

	i = -1;
	array = (char **)malloc(sizeof(char *));
	if (!array)
		return (NULL);
	array[0] = NULL;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|'){
			line = redirect_parse(line, &i, envp);
			tmp = ft_substr(line, 0, find_redir(line));
			array = add_val(array, tmp);
			line = ft_substr(line, find_redir(line), ft_strlen(line) - find_redir(line));
			i = 0;
			if (line[i + 1] == '>' || line[i] == '<')
			{
				tmp = ft_substr(line, 0, i + 2);
				line = ft_strdup(line + i + 2);
			}
			if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			{
				tmp = ft_substr(line, 0, i + 1);
				line = ft_strdup(line + i + 1);
			}
			array = add_val(array, tmp);;
			i = -1;
		}
	}
	i = 0;
	if (line[i] == ' ')
	{
		while (line[i] == ' ')
			i++;
		line = ft_substr(line, i, ft_strlen(line) - i);
	}
	while (line[i++])
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
	array = add_val(array, line);
	// free(line);
	return (array);
}