/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:49:50 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/13 20:12:02 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		i;
	int		j;

	ret = NULL;
	if (!(ret = ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j])
		ret[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}
