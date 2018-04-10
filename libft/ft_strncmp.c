/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:45:53 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:47:47 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	unsigned	char	cs1;
	unsigned	char	cs2;

	if (!n)
		return (0);
	i = 0;
	cs1 = (unsigned char)s1[i];
	cs2 = (unsigned char)s2[i];
	while (cs1 && cs2 && i < n)
	{
		cs1 = (unsigned char)s1[i];
		cs2 = (unsigned char)s2[i];
		if (cs1 != cs2)
			return (cs1 - cs2);
		i++;
	}
	return (cs1 - cs2);
}
