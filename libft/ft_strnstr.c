/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:46:10 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:49:38 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	int		k;
	int		save;

	i = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (str[i] && i < len)
	{
		k = 0;
		save = i;
		while (str[i++] == to_find[k++] && i < len + 1)
			if (to_find[k] == '\0')
				return ((char *)str + save);
		i = (i - k) + 1;
	}
	return (NULL);
}
