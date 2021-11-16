/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:21:30 by heveline          #+#    #+#             */
/*   Updated: 2021/11/16 21:45:07 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strequal(const char *str1, const char *str2)
{
	while ((*str1 == *str2) && *str1 && *str2)
	{	
		str1++;
		str2++;
	}
	return (!((unsigned char)*str1 - (unsigned char)*str2));
}

int	check_redir_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			return (1);
		i++;
	}
	return (0);
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

size_t	ft_arraylen(char **str)
{
	size_t	n;

	n = 0;
	while (*str++)
		n++;
	return (n);
}
