/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:49:50 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/21 14:07:54 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
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
	while (s2 && s2[j] && j < (int)n)
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}
