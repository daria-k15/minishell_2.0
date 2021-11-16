/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 23:01:24 by heveline          #+#    #+#             */
/*   Updated: 2021/11/16 23:01:26 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_exit(const int *id)
{
	static int	status;

	if (id)
		status = *id;
	return (status);
}

int	get_exit(void)
{
	return (new_exit(NULL));
}

void	set_exit(int id)
{
	new_exit(&id);
}
