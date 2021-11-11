/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heveline <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:36:26 by heveline          #+#    #+#             */
/*   Updated: 2021/04/20 19:53:48 by heveline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strrchr(const char *str, int ch)
{
	int			i;
	const char	*a;

	a = str;
	i = ft_strlen(str);
	str = str + i;
	while (str != a && *str != ch)
		str--;
	if (*str == ch)
		return ((char *)str);
	return (0);
}
