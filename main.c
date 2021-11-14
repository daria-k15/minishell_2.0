#include "minishell.h"

size_t	ft_arraylen(char **str)
{
	size_t	n;

	n = 0;
	while (*str++)
		n++;
	return (n);
}

t_ctrl	*ctrl_init(char **envp, int argc, char **argv)
{
	t_ctrl	*control;

	(void)argc;
	(void)argv;
	control = malloc(sizeof(t_ctrl));
	control->env = env_init(envp);
	control->fd_in = dup(STDIN_FILENO); //need to change to dup2(int, int)
	control->fd_out = dup(STDOUT_FILENO); //same
	control->pid = 1;
	return (control);
}

void tree_free(t_ast **tree)
{
	if (*tree)
	{
		if ((*tree)->left != NULL)
			tree_free(&(*tree)->left);
		if ((*tree)->right != NULL)
			tree_free(&(*tree)->right);
		if ((*tree)->value)
			free((*tree)->value);/* code */
		//if ((*tree)->prior)
		//	free((*tree)->prior);/* code */
		free((*tree));
	}
	(*tree) = NULL;
}

void	tree(char **array, t_ctrl *control, char **envp)
{
	t_ast	*ast;

	ast = NULL;
	ast = tree_create(ast, array);
	tree_print_rec(ast, 0);
	tree_handle(ast, control, envp);
	tree_free(&ast);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**array;
	t_ctrl	*control;

	control = ctrl_init(env, ac, av);
	while (1)
	{
		sighandler();
		line = readline("Z&D_Shell: ");
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (!line[0])
		{
			free(line);
			continue ;
		}
		add_history(line);
		array = parsing(line, env);
		if (!array || !array[0])
			continue;
		tree(array, control, env);
	}
	clear_history();
	ctrl_free(control);
	return (EXIT_SUCCESS);
}
