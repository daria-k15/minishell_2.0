#include "minishell.h"

static void write_to_tmp(t_ast *ast, int fd)
{
    char *buf;
    while (1)
    {
        buf = readline("> ");
        if (!buf)
            
        ft_strequal(buf, ast->right->value);
        ft_putendl_fd(buf, fd);
        free(buf);
    }
    
}

static void heredoc_func(t_ast *ast)
{
    int here;
    char *stop;
    int i;
    char *name;

    i = 0;
    
    if (!ast)
        return ;
    if (ft_strequal(ast->value, "<<"))
    {
        name = ft_strjoin("/tmp/.tmp_heredoc", ft_itoa(i));
        here = open(name, O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
        write_to_tmp(ast->right, here);
        i++;
        free(name);
        close(here);        
    }
    heredoc_func(ast->left);
    heredoc_func(ast->right);
}

char *tree_single_quote(char *line, int *i)
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
}

char *tree_double_quote(char *line, int *i, char **envp)
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
}

char *tree_skip_space(char *line, int *i)
{
	int j = *i;

	while (line[j] == ' ')
		j++;
	line = ft_substr(line, j, ft_strlen(line));
	return (line);
}

char **split_values(char *line, char **env)
{
	char **array;
	int i;
	char *tmp;

	i = -1;
	array = (char **)malloc(sizeof(char *));
	if (!array)
		return (0);
	array[0] = NULL;
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
			// free(tmp);
			i = -1;
		}
	}
	array = add_val(array, line);
	return (array);
}

void go_through_tree(t_ast *ast, t_data *data, char **envp)
{
    int pid;
    int i;
    char **cmd_array;
	i = -1;
    if (check_redir(ast))
    {
        heredoc_func(ast);
    }
    // cmd_array = ft_split(ast->value, ' ');
	cmd_array = split_values(ast->value, envp);
	// while (cmd_array[++i])
	// {
	// 	printf("array[%d] = %s\n", i, cmd_array[i]);
	// 	// i++;
	// }
    if (ft_strequal(cmd_array[0], "env"))
        env_builtin(data->env);
      else if (ft_strequal(cmd_array[0], "export"))
        export_builtin(cmd_array, &(data->env));
      else if (ft_strequal(cmd_array[0], "unset"))
        unset_builtin(cmd_array, &(data->env));
      else if (ft_strequal(cmd_array[0], "echo"))
        echo_builtin(cmd_array);
      else if (ft_strequal(cmd_array[0], "cd"))
        cd_builtin(cmd_array, &(data->env));
      else if (ft_strequal(cmd_array[0], "exit"))
        exit_builtin();
      else if (ft_strequal(cmd_array[0], "pwd"))
        pwd_builtin();
      else
        binary_command(cmd_array, &(data->env));
    free_array(cmd_array);
}