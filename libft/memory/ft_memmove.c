/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 18:36:41 by heveline          #+#    #+#             */
/*   Updated: 2021/04/20 20:53:47 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*t_dst;
	unsigned char	*t_src;

	t_dst = (unsigned char *)dst;
	t_src = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (src <= dst)
	{
		while (n--)
			t_dst[n] = t_src[n];
	}
	else
	{
		while (n != 0)
		{
			*t_dst++ = *t_src++;
			n--;
		}
	}
	return ((unsigned char *)dst);
}
