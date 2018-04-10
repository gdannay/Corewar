/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:44:16 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:32:45 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void			*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	int					j;
	unsigned	char	*str;
	unsigned	char	*move;

	i = -1;
	j = n;
	str = (unsigned char *)src;
	move = (unsigned char *)dest;
	if (dest - src <= 0)
	{
		while (++i < n)
			move[i] = str[i];
	}
	else
	{
		while (--j >= 0)
			move[j] = str[j];
	}
	return (dest);
}
