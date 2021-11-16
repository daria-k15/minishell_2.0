/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:56:50 by heveline          #+#    #+#             */
/*   Updated: 2021/11/16 16:56:58 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_sighand(int signal)
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

void	handlerquit(int signum)
{
	(void)signum;
	printf("Quit: 3\n");
	set_exit(131);
}
