/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:45:26 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 21:19:23 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (!(ret = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}
