/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:50:46 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:53:24 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	int		i;

	if (s == NULL)
		return (NULL);
	ret = NULL;
	if (!(ret = (char *)ft_memalloc(len + 1)))
		return (NULL);
	i = 0;
	while (len > 0)
	{
		ret[i] = s[start + i];
		i++;
		len--;
	}
	ret[i] = '\0';
	return (ret);
}
