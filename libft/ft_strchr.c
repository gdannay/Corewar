/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:44:41 by clegirar          #+#    #+#             */
/*   Updated: 2018/04/19 14:47:10 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (s[i] == (unsigned char)c)
		return ((char *)&(s[i]));
	while (s[i])
	{
		if (s[i + 1] == (unsigned char)c)
			return ((char *)&(s[i + 1]));
		i++;
	}
	return (NULL);
}
