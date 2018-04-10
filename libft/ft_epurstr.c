/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epurstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:21:19 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 17:40:00 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		len_epur(char *str)
{
	int		i;
	int		len;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	len = 0;
	while (str[i])
	{
		if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			while (str[i] && str[i] != ' '
					&& str[i] != '\t' && str[i] != '\n')
			{
				i++;
				len++;
			}
			len++;
		}
		else
			i++;
	}
	return (len);
}

char			*ft_epurstr(char *str)
{
	char	*ret;
	int		i;
	int		j;
	int		len;

	len = len_epur(str);
	if (!(ret = (char *)ft_memalloc(len)))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			while (str[i] && str[i] != ' '
					&& str[i] != '\t' && str[i] != '\n')
				ret[j++] = str[i++];
			if (j + 1 < len)
				ret[j++] = ' ';
		}
		else
			i++;
	}
	ret[j] = '\0';
	return (ret);
}
