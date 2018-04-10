/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:44:05 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:31:55 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	size_t				j;
	unsigned	char	*str;
	unsigned	char	*ret;

	i = 0;
	j = 0;
	ret = (unsigned char *)dest;
	str = (unsigned char *)src;
	while (i < n)
		ret[j++] = str[i++];
	return (dest);
}
