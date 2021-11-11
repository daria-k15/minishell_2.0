/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:24:41 by heveline          #+#    #+#             */
/*   Updated: 2021/04/21 18:41:57 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t t)
{
	char	*dst;
	size_t	i;

	i = count * t;
	dst = malloc(i);
	if (!dst)
		return (NULL);
	ft_memset(dst, 0, i);
	return (dst);
}
