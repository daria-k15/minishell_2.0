#include "minishell.h"

void	print_her(char *str, int fd)
{
	int	i;

	rl_redisplay();
	i = 0;
	while (str[i] != '\0')
		write(fd, &str[i++], 1);
	free(str);
}

static void write_to_tmp(t_ast *ast, int fd)
{
    char *buf;
	char *line;
	int i;

	line = malloc(sizeof(char));
	*line = '\0';
    while (1)
    {
        buf = readline("> ");
        if (!buf)
		{
			print_her(line, fd);
			return ;
		}
		if (ft_strcmp(line, ast->value) == 0)
		{
			i = 0;
			while (line[i] != '\0')
				write(fd, &line[i++], 1);
			free(line);
			free(buf);
			break ;
		}
            
        // ft_strequal(buf, ast->right->value);
        // ft_putendl_fd(buf, fd);
        // free(buf);
    }
    
}



t_ast_data  *create_ast_data(void)
{
    t_ast_data  *val;

    val = malloc(sizeof(t_ast_data));
    if (!val)
        return(NULL);
    val->file = NULL;
    val->in = 0;
    val->out = 1;
    val->pipe = NULL;
    return (val);
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

void    create_files(t_ast_data *val, int fd)
{
    int *tmp;
    int i;

    i = 0;
    if (val->file)
    {
        while(val->file[i] != -1)
            i++;
    }
	tmp = malloc(sizeof(int) * (i + 2));
    if (i != 0)
    {
        i = 0;
        while (val->file[i] != -1)
        {
            tmp[i] = val->file[i];
            i++;
        }
        free(val->file);
    }
    tmp[i++] = fd;
    tmp[i] = -1;
    val->file = tmp;
}

void clean_node(t_ast *ast, t_ctrl *data, t_ast_data *val)
{
	ast_data_free(val);
	ctrl_free(data);
	tree_free(&ast);
}

void empty_cmd(t_ast *ast, t_ctrl *data, t_ast_data *val, char **array)
{
	free(array);
	clean_node(ast, data, val);
}

void    cmd_commands(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp)
{
        char    **cmd_array;


        cmd_array = split_values(ast->value, envp);
		if (cmd_array[0] == NULL)
		{
			empty_cmd(ast, control, val, cmd_array);
			exit(0);
		}
		if (ft_strcmp(cmd_array[0], "env") == 0)
			env_builtin(cmd_array, control->env, val->out);
		else if (ft_strcmp(cmd_array[0], "export") == 0)
			export_builtin(cmd_array, &(control->env), val->out);
		else if (ft_strcmp(cmd_array[0], "unset") == 0)
			unset_builtin(cmd_array, &(control->env), val->out);
		else if (ft_strcmp(cmd_array[0], "echo") == 0)
			echo_builtin(cmd_array, val->out);
		else if (ft_strcmp(cmd_array[0], "cd") == 0)
			cd_builtin(cmd_array, &(control->env));
		else if (ft_strcmp(cmd_array[0], "exit") == 0)
			exit_builtin(cmd_array, val->out);
		else if (ft_strcmp(cmd_array[0], "pwd") == 0)
			pwd_builtin(cmd_array, val->out);
		else
			binary_command(ast, cmd_array, &(control->env), control, val);
		if (!control->pid)
			exit(get_exit());
}

void	ctrl_free(t_ctrl *control)
{
	free_env(control->env);
	free(control);
}

void	ast_data_default(t_ast_data *val)
{
	int	i;
/*
	if (val->pipe)
	{
		i = 0;
		while (val->pipe[i] != -1)
			close(val->pipe[i++]);
		free(val->pipe);
		val->pipe = NULL;
	}*/
	if (val->file)
	{
		i = 0;
		while (val->file[i] != -1)
			close(val->file[i++]);
		free(val->file);
		val->file = NULL;
	}
	val->in = 0;
	val->out = 1;
}

void	ast_data_free(t_ast_data *val)
{
	ast_data_default(val);
	free(val);
}

void    go_through_nodes(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp)
{
    if (!ast)
	{
		if (control->pid == 0)
		{
			ctrl_free(control);
			ast_data_free(val);
			tree_free(&ast);
			exit(0);
		}
		else
			return;
	}
    else if (!ft_strcmp((char *)ast->value, ">") || !ft_strcmp((char *)ast->value, ">>"))
        right_redir(ast, control, val, envp);
	else if (ft_strcmp((char *)ast->value, "<") == 0 || ft_strequal((char *)ast->value, "<<"))
		left_redir(ast, control, val, envp);
    else if (ft_strcmp(ast->value, "|") == 0)
		pipe_func(ast, control, val, envp);
	else
        cmd_commands(ast, control, val, envp);
}

static void heredoc_func(t_ast *ast, t_ctrl *control)
{
    int i;
    
    if (!ast)
        return ;
    if (ft_strcmp(ast->value, "<<") == 0)
    {
        i = open("/tmp/.tmp_heredoc", O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
        write_to_tmp(ast->right, i);
		close(i);        
    }
    heredoc_func(ast->left, control);
    heredoc_func(ast->right, control);
}


void tree_handle(t_ast *ast, t_ctrl *control, char **envp)
{
    pid_t     pid;
    int     status;
    t_ast_data  *val;

    if (check_hero(ast))
    {
        pid = fork();
        signal(SIGINT, SIG_IGN);
        if (pid == 0)
        {
            tree_sighandler();
            heredoc_func(ast, control);
			exit(0);
        }
        waitpid(pid, &status, 0);
		if (WTERMSIG(status) == SIGINT)
			exit(1);
		else
			exit(status/256);
    }
    val = create_ast_data();
    go_through_nodes(ast, control, val, envp);
	ast_data_free(val);
}