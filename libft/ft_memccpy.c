/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:43:35 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:30:50 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned	char	c2;
	unsigned	char	*str;
	unsigned	char	*ret;

	i = 0;
	c2 = (unsigned char)c;
	str = (unsigned char *)src;
	ret = (unsigned char *)dest;
	while (i < n && str[i] != c2)
	{
		ret[i] = str[i];
		i++;
	}
	if (i == n)
		return (NULL);
	ret[i] = str[i];
	return ((void*)ret + i + 1);
}
