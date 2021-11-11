#include "minishell.h"

size_t	ft_arraylen(char **str)
{
	size_t	n;

	n = 0;
	while (*str++)
		n++;
	return (n);
}

t_data	*create_data(char **envp, int argc, char **argv)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	data->env = env_init(envp);
	data->fd_in = dup(STDIN_FILENO); //need to change to dup2(int, int)
	data->fd_out = dup(STDOUT_FILENO); //same
	data->pid = 1;
	return (data);
}

void	tree_handling(char **array, t_data *data, char **envp)
{
	t_ast	*ast;

	ast = NULL;
	ast = create_tree(ast, array);
	// print_tree_rec(ast, 0);
	tree_handle(ast, data, envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**array;
	t_data	*data;

	data = create_data(envp, argc, argv);
	while (1)
	{
		line = start_loop();
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		array = parsing(line, envp);
		tree_handling(array, data, envp);
	}
	clear_history();
	return (EXIT_SUCCESS);
}
