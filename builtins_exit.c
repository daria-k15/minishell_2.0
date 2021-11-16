/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:31:12 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 20:54:06 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	numeric_condition(unsigned long long *exit_num, int neg)
{
	if ((*exit_num > (unsigned long long)9223372036854775807 && neg == 1)
		|| (*exit_num > (unsigned long long)9223372036854775808 && neg == -1))
		return (1);
	return (0);
}

static int	numeric(char *number, unsigned long long *exit_num)
{
	int	neg;
	int	i;

	i = 0;
	neg = 1;
	if (number[i] == '-')
	{
		i++;
		neg = -1;
	}
	while (number[i])
	{
		if (!ft_isdigit(number[i]) || numeric_condition(exit_num, neg))
			return (0);
		*exit_num = (10 * *exit_num + (number[i++] - 48));
	}
	if (numeric_condition(exit_num, neg))
		return (0);
	if (*exit_num == (unsigned long long)9223372036854775808)
		*exit_num = (long long)(neg * (*exit_num));
	else
		*exit_num = (long long)neg * (*exit_num);
	return (1);
}

void	exit_builtin(char **cmd_array, t_ctrl *control, int fdout)
{
	unsigned long long	exit_num;

	exit_num = 0;
	if (ft_arraylen(cmd_array) > 1 && !numeric(cmd_array[1], &exit_num))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		ft_putstr_fd(control->mininame, STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd_array[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		free_array(cmd_array);
		exit(255);
	}
	else if (ft_arraylen(cmd_array) > 2)
	{
		ft_putstr_fd(control->mininame, STDERR_FILENO);
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		set_exit(1);
		return ;
	}
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit((unsigned char)exit_num);
	}
}
