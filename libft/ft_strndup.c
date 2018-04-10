/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:45:26 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 14:56:15 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*ret;
	int		i;
	int		j;

	if (!s || n <= 0)
		return (NULL);
	if (!(ret = ft_memalloc(n + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && i < n)
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}
