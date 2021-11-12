#include "minishell.h"

void	handlerint(int signal)
{
	(void)signal;
	write(2, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	sighandler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handlerint);
}

void tree_sighand(int signal)
{
	signal = 0;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	exit(1);
}

void	tree_sighandler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, tree_sighand);
}

char	*start_loop(void)
{
	sighandler();
	return (readline("Z&D_Shell: "));
	// return ("echo hello >> a");
}
