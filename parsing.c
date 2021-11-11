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

char *single_quote_parse(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	if (check_char(line, '\'', j + 1) == 1)
	{
		while (line[++(*i)])
		{
			if (line[(*i)] == '\'')
				break ;
		}
		tmp = ft_substr(line, 0, j);
		tmp2 = ft_substr(line, j + 1,  *i - j - 1);
		tmp = ft_strjoin(tmp, tmp2);
		tmp3 = ft_strdup(line + *i + 1);
		tmp3 = ft_strjoin(tmp, tmp3);
		return (tmp3);
	}
	else{
		write(2, "Syntax error!\n", ft_strlen("Syntax error!\n"));
		exit(1);
	}
	return (line);
}

char	*double_quote_parse(char *line, int *i, char **envp)
{
	int j = *i;
	char *tmp;
	char *tmp2;
	char *tmp3;

	if (check_char(line, '\"', j + 1) == 1)
	{
		while (line[++(*i)])
		{
			if (line[*i] == '\\' && (line[*i + 1] == '\"' || line[*i + 1] == '$' || line[*i + 1] == '\\'))
				line = slash_parse(line, i);
			if (line[*i] == '$')
				line = parse_dollar(line, i, envp);
			if (line[*i] == '\"')
				break ;
		}
		tmp = ft_substr(line, 0, j);
		tmp2 = ft_substr(line, j+ 1,  *i -j - 1);
		tmp3 = ft_strdup(line + *i + 1);
		tmp = ft_strjoin(tmp, tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		(*i)--;
		return (tmp);
	}
	else{
		write(2,"Syntax error!\n", ft_strlen("Syntax error!\n"));
		exit(1);
	}
	return (line);
}

char *skip_space(char *line, int *i)
{
	int j = *i;
	char *tmp;
	char *tmp1;
	// char *res;
	// int k = -1;

	while (line[j] == ' ')
		j++;
	tmp = ft_substr(line, 0, *i + 1);
	tmp1 = ft_substr(line, j, ft_strlen(line));
	tmp1 = ft_strjoin(tmp, tmp1);
	return (tmp1);
}

char *redirect_parse(char *line, t_ast **ast, int *i, char **envp)
{
	int j = *i;
	int k = -1;
	char *tmp;
	// char *tmp1;
	int l = 0;

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
		if (tmp[k] == '\"')
			tmp = double_quote_parse(tmp, &k, envp);
		if (tmp[k] == '\'')
			tmp = single_quote_parse(tmp, &k);
		if (tmp[k] == '$')
			tmp = parse_dollar(tmp, &k, envp);
		if (tmp[k] == '\\')
			tmp = slash_parse(tmp, &k);
		if (tmp[k] == ' ')
			tmp = skip_space(tmp, &k);
	}
	line = ft_strdup(line + j);
	j = 0;
	if (line[j + 1] == '>' || line[j + 1] == '<')
	{
		if (*ast == NULL){
			*ast = create_node(tmp);
			add_value(ast, ft_substr(line, 0, j + 2));
		}
		else
		{
			add_value(ast, tmp);
			add_value(ast, ft_substr(line, 0, j + 2));
		}
		line = ft_strdup(line + j + 2);
	}
	else
	{
		if (*ast == NULL)
		{
			*ast = create_node(tmp);
			add_value(ast, ft_substr(line, 0, j + 1));
		}
		else
		{
			add_value(ast, tmp);
			add_value(ast, ft_substr(line, 0, j + 1));
		}
		line = ft_strdup(line + j + 1);
	}
	return (line);
}



t_ast	*parsing(char *line, char **envp)
{
	int i;
	// int j = -1;
	t_ast *ast;
	// char *tmp;
	// char **array;
	
	i = -1;
	ast = NULL;

	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|'){
			line = redirect_parse(line, &ast, &i, envp);
			i = -1;
		}
	}
	i = 0;
	if (line[i] == ' ')
		line = ft_substr(line, 1, ft_strlen(line) - 1);
	if (ast == NULL)
	{
		i = -1;
		while (line[++i])
		{
			if (line[i] == '\"')
				line = double_quote_parse(line, &i, envp);
			if (line[i] == '\'')
				line = single_quote_parse(line, &i);
			if (line[i] == '$')
				line = parse_dollar(line, &i, envp);
			if (line[i] == '\\')
				line = slash_parse(line, &i);
			if (line[i] == ' ')
				line = skip_space(line, &i);
		}
		if (ast == NULL)
			ast = create_node(line);
	}
	else
		add_value(&ast, line);
	return (ast);
}
