/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:56:31 by heveline          #+#    #+#             */
/*   Updated: 2021/04/20 18:05:05 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*t_src;

	i = 0;
	t_src = (unsigned char *)src;
	while (i < n)
	{
		if (t_src[i] == (unsigned char)c)
			return (t_src + i);
		i++;
	}
	return (0);
}
