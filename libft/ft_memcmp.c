/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:43:57 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:31:38 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	size_t				j;
	unsigned	char	*str;
	unsigned	char	*str2;

	if (!n)
		return (0);
	i = 0;
	j = 0;
	str = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n - 1)
	{
		if (str[i] != str2[j])
			return (str[i] - str2[j]);
		i++;
		j++;
	}
	return (str[i] - str2[j]);
}
