/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   love_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <heveline@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 21:13:34 by qcesar            #+#    #+#             */
/*   Updated: 2021/11/17 01:53:46 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**love_norme(char **array, int i)
{
	array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	return (array);
}
