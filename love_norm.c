/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   love_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qcesar <qcesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:13:34 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/16 21:28:35 by qcesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**love_norme(char **array, int i)
{
	array = (char **)malloc(sizeof(char *) * i);
	if (!array)
		return (NULL);
	return (array);
}
