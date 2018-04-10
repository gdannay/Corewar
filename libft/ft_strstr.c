/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:46:38 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/30 16:00:13 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int	i;
	int	k;
	int	save;

	i = 0;
	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (str[i])
	{
		k = 0;
		save = i;
		while (str[i++] == to_find[k++])
			if (to_find[k] == '\0')
				return ((char *)str + save);
		i = (i - k) + 1;
	}
	return (NULL);
}
