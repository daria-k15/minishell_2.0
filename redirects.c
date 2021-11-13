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

void pipe_child(t_ast *ast, t_ctrl *control, t_ast_data *val,char **envp)
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
		go_through_nodes(ast->left, control, val, envp);
		close(pipe_des[1]);
	}
	else
	{
		close(pipe_des[1]);
		if (dup2(pipe_des[0], STDIN_FILENO) == -1)
			ft_err("dup2");
		go_through_nodes(ast->right, control, val, envp);
		close(pipe_des[0]);
		waitpid(fork_pid, NULL, 0);
	}
	exit(1);

}

void pipe_func(t_ast *ast, t_ctrl *control, t_ast_data *val,char **envp)
{
	int fork_pid;

	fork_pid = fork();
	//check condition here

	if (fork_pid == 0)
	{
		control->pid = 0;
		pipe_child(ast, control, val, envp);
	}
	else
	{
		waitpid(fork_pid, NULL, 0);
	//	control->exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : g_sig;
	}
}