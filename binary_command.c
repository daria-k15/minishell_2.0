#include "minishell.h"

char	*path_handler(char *cmd, char **env)
{
	int		i;
	char	**path_list;
	char	*temp;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		ft_err("Error: problem with ENV, no PATHs found");
	path_list = ft_split(env[i] + 5, ':');
	i = 0;
	while (path_list[i])
	{
		path_list[i] = ft_strjoin(path_list[i], "/");
		temp = ft_strjoin(path_list[i], cmd);
		if (access(temp, F_OK) == 0)
			return (temp);
		i++;
	}
	ft_err("Error: no binary found for the command");
	return (NULL);
}

void  binary_command(t_ast *ast, char **cmd_array, t_env **env_list, t_ctrl *control, t_ast_data *val)
{
	char	**env;
	char	*path;
	pid_t	pid;
	int i;

	pid = 1;
	if (control->pid != 0)
		pid = fork();
	if (pid < 0)
		{
			ft_putendl_fd("Fork error", STDERR_FILENO);
			set_exit(228);
		}
	if (pid == 0 || control->pid == 0)
	{
		if (dup2(val->out, STDOUT_FILENO) < 0)
			ft_err("error in dup");
		if (dup2(val->in, STDIN_FILENO)< 0)
			ft_err("error in dup");
		tree_free(&ast);
		ast_data_free(val);
		env = env_to_array(env_list);
		path = path_handler(cmd_array[0], env);
		if (execve(path, cmd_array, env) == -1)
			ft_err("Error: command not executable");
	}
	waitpid(pid, &i, 0);
	set_exit(i/256);
}