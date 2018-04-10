/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:37:48 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:40:48 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (dst[i] && size)
	{
		i++;
		size--;
	}
	j = 0;
	if (size == 0)
		return (i + ft_strlen(src));
	while (src[j] && size != 1)
	{
		dst[i] = src[j];
		i++;
		j++;
		size--;
	}
	dst[i] = '\0';
	return (i + ft_strlen(src) - j);
}
