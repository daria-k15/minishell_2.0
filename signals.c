/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:19:37 by heveline          #+#    #+#             */
/*   Updated: 2021/11/16 21:28:00 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handlerint(int signal)
{
	signal = 0;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit(1);
}

void	sighandler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handlerint);
}

void	handlerintproc(int signum)
{
	(void)signum;
	set_exit(130);
	printf("\n");
	rl_on_new_line();
}

void	sigproc(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, handlerquit);
	signal(SIGINT, handlerintproc);
}
