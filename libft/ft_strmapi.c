/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:50:08 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:46:13 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned	int	i;
	unsigned	int	j;

	if (s == NULL)
		return (NULL);
	ret = NULL;
	if (!(ret = (char *)ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		ret[j] = f(i, s[i]);
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
