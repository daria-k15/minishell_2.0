#include "minishell.h"

int	check_arg(char *arg)
{
	if (ft_strcmp("echo", arg) == 0 || ft_strcmp("cd", arg) == 0
		|| ft_strcmp("pwd", arg) == 0 || ft_strcmp("export", arg) == 0
		|| ft_strcmp("unset", arg) == 0 || ft_strcmp("env", arg) == 0
		|| ft_strcmp("exit", arg) == 0)
	{
		return (1);
	}
	return (0);
}

int check_hero(t_ast *ast)
{
	if (ft_strcmp(ast->value, "<<") == 0)
		return (1);
	return (0);
}

int	check_redir(t_ast *ast)
{
	if (ft_strcmp(ast->value, ">") == 0 || ft_strcmp(ast->value, ">>") == 0
		|| ft_strcmp(ast->value, "<") == 0 || ft_strcmp(ast->value, "<<") == 0)
		return (1);
	return (0);
}

void	ft_err(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str[i]);
	free(str);
}
