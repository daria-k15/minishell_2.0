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

static void heredoc_func(t_ast *ast, t_data *data)
{
    // int here;
    // char *stop;
    int i;
    // char *name;

    // i = 0;
    
    if (!ast)
        return ;
    if (ft_strcmp(ast->value, "<<") == 0)
    {
        // name = ft_strjoin("/tmp/.tmp_heredoc", ft_itoa(i));
        i = open("/tmp/.tmp_heredoc", O_CREAT | O_TRUNC | O_WRONLY,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
        write_to_tmp(ast->right, i);
        i++;
        // free(name);
        close(i);        
    }
    heredoc_func(ast->left, data);
    heredoc_func(ast->right, data);
}

t_ast_data  *create_ast_data(void)
{
    t_ast_data  *val;

    val = malloc(sizeof(t_ast_data));
    if (!val)
        return(NULL);
    val->end = 0;
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

void    cmd_commands(t_ast *ast, t_data *data, t_ast_data *val, char **envp)
{
        char    **cmd_array;

        cmd_array = split_values(ast->value, envp);
    	if (ft_strcmp(cmd_array[0], "env") == 0)
			env_builtin(cmd_array, data->env, val->out);
		else if (ft_strcmp(cmd_array[0], "export") == 0)
			export_builtin(cmd_array, &(data->env), val->out);
		else if (ft_strcmp(cmd_array[0], "unset") == 0)
			unset_builtin(cmd_array, &(data->env), val->out);
		else if (ft_strcmp(cmd_array[0], "echo") == 0)
			echo_builtin(cmd_array, val->out);
		else if (ft_strcmp(cmd_array[0], "cd") == 0)
			cd_builtin(cmd_array, &(data->env), val->out);
		else if (ft_strcmp(cmd_array[0], "exit") == 0)
			exit_builtin(cmd_array, val->out);
		else if (ft_strcmp(cmd_array[0], "pwd") == 0)
			pwd_builtin(cmd_array, val->out);
		else
			binary_command(cmd_array, &(data->env), data, val);
		
}

void	left_redir(t_ast *ast, t_data *data, t_ast_data *val, char **envp)
{
	int i;

    i = open((char *)ast->right->value, O_CREAT | O_TRUNC | O_WRONLY,
			 S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	if (i == -1)
	{
		ft_putstr_fd("Z&D Shell: ", STDERR_FILENO);
		ft_putstr_fd(ast->right->value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		val->end = 1;
	}
	else
	{
		create_files(val, i);
		val->in = i;
		go_through_nodes(ast->left, data, val, envp);
	}
}

void    right_redir(t_ast *ast, t_data *data, t_ast_data *val,char **envp)
{
    int i;
	
	if (!ft_strcmp((char *)ast->value, ">>"))
		i = open((char *)ast->right->value, O_CREAT | O_APPEND | O_WRONLY,
			 S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	else
    	i = open((char *)ast->right->value, O_CREAT | O_TRUNC | O_WRONLY,
			 S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	if (i == -1)
	{
		ft_putstr_fd("Z&D Shell: ", STDERR_FILENO);
		ft_putstr_fd(ast->right->value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		val->end = 1;
	}
	else
	{
		create_files(val, i);
		val->out = i;
		go_through_nodes(ast->left, data, val, envp);
	}
}

void pipe_child(t_ast *ast, t_data *data, t_ast_data *val,char **envp)
{
	int fork_pid;
	int pipe_des[2];

	if (pipe(pipe_des) < 0)
		ft_err("pipe problem");
	fork_pid = fork();
	//check for -1

	if (fork_pid == 0)
	{
		close(pipe_des[0]);
		if (dup2(pipe_des[1], STDOUT_FILENO) == -1)
			ft_err("dup2");
		go_through_nodes(ast->left, data, val, envp);
		close(pipe_des[1]);
	}
	else
	{
		close(pipe_des[1]);
		if (dup2(pipe_des[0], STDIN_FILENO) == -1)
			ft_err("dup2");
		go_through_nodes(ast->right, data, val, envp);
		close(pipe_des[0]);
		waitpid(fork_pid, NULL, 0);
	}
	exit(1);

}

void pipe_func(t_ast *ast, t_data *data, t_ast_data *val,char **envp)
{
	int fork_pid;

	fork_pid = fork();
	//check condition here

	if (fork_pid == 0)
		pipe_child(ast, data, val, envp);
	else
	{
		waitpid(fork_pid, NULL, 0);
	//	control->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : g_sig;
	}
}

void    go_through_nodes(t_ast *ast, t_data *data, t_ast_data *val, char **envp)
{
    if (!ast)
        return ;
    else if (!ft_strcmp((char *)ast->value, ">") || !ft_strcmp((char *)ast->value, ">>"))
        right_redir(ast, data, val, envp);
	else if (ft_strcmp(ast->value, "<") == 0)
		left_redir(ast, data, val, envp);
    else if (ft_strcmp(ast->value, "|") == 0)
		pipe_func(ast, data, val, envp);
	else
    {
        cmd_commands(ast, data, val, envp);
        val->end = 1;
    }
}

void tree_handle(t_ast *ast, t_data *data, char **envp)
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
            heredoc_func(ast, data);
			exit(0);
        }
        waitpid(pid, &status, 0);
		if (WTERMSIG(status) == SIGINT)
			exit(1);
		else
			exit (status / 256);
    }
    val = create_ast_data();
    go_through_nodes(ast, data, val, envp);
}