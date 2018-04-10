/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:44:25 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:33:10 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned	char	*str;
	unsigned	char	c2;
	size_t				i;

	str = (unsigned char *)s;
	c2 = (unsigned char)c;
	i = 0;
	while (i < n)
		str[i++] = c2;
	return (s);
}
