#include "minishell.h"

void	left_redir(t_ast *ast, t_ctrl *control, t_ast_data *val, char **envp)
{
	int i;

    if (ft_strequal(ast->value, "<"))
		i = open((char *)ast->right->value, O_RDONLY,
			 S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	else if (ft_strequal(ast->value, "<<"))
		i = open("/tmp/.tmp_heredoc", O_RDONLY,
			 S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	if (i == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(ast->right->value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
	{
		create_files(val, i);
		val->in = i;
		go_through_nodes(ast->left, control, val, envp);
	}
}

void    right_redir(t_ast *ast, t_ctrl *control, t_ast_data *val,char **envp)
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
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(ast->right->value, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
	{
		create_files(val, i);
		val->out = i;
		go_through_nodes(ast->left, control, val, envp);
	}
}
/*
void pipe_child(t_ast *ast, t_ctrl *control, t_ast_data *val,char **envp)
{
	int fork_pid;

	fork_pid = fork();
	//check for -1

	if (fork_pid == 0)
	{
		
		if (dup2(pipe_des[1], STDOUT_FILENO) == -1)
			ft_err("dup2");
		close(pipe_des[0]);
		close(pipe_des[1]);
		go_through_nodes(ast->left, control, val, envp);
	}
	else
	{
		if (dup2(pipe_des[0], STDIN_FILENO) == -1)
			ft_err("dup2");
		close(pipe_des[1]);
		close(pipe_des[0]);
		waitpid(fork_pid, NULL, 0);
		go_through_nodes(ast->right, control, val, envp);
	}
	exit(1);

}*/

void pipe_func(t_ast *ast, t_ctrl *control, t_ast_data *val,char **envp)
{
	int fork_pid[2];
	int pipe_des[2];
	int status;

	if (pipe(pipe_des) < 0)
		ft_err("pipe problem");

	
	//check condition here
	val->out = pipe_des[1];
	fork_pid[0] = fork();
	if (fork_pid[0] == 0)
	{
		control->pid = 0;
		go_through_nodes(ast->left, control, val, envp);
	}
	ast_data_default(val);
	val->in = pipe_des[0];
	
	ft_putendl_fd("hey1", 2);
	fork_pid[1] = fork();
	if (fork_pid[1] == 0)
	{
		ft_putendl_fd("hey2", 2);
		ft_putnbr_fd(getpid(), 2);
		ft_putendl_fd("", 2);
		control->pid = 0;
		go_through_nodes(ast->right, control, val, envp);
		ft_putendl_fd("hey4", 2);
	}
	close(pipe_des[0]);
	close(pipe_des[1]);
	ft_putendl_fd("hey3", 2);
	ft_putnbr_fd(getpid(), 2);
	ft_putendl_fd("", 2);
	waitpid(fork_pid[0], 0, 0);
	waitpid(fork_pid[1], &status, 0);
	set_exit(status/256);
	if (control->pid == 0)
		exit(get_exit());
	//	control->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : g_sig;
	
}