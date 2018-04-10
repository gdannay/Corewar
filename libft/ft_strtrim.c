/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:50:54 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:55:53 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		len_strtrim(char const *s)
{
	int		i;
	int		len;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	if (s[i] == '\0')
		return (0);
	len = 0;
	while (s[i])
	{
		len++;
		i++;
	}
	i--;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
	{
		i--;
		len--;
	}
	return (len);
}

static	int		len_end(char const *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
		i++;
	i--;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
	{
		i--;
		len++;
	}
	return (len);
}

char			*ft_strtrim(char const *s)
{
	char	*ret;
	size_t	i;
	int		j;

	if (s == NULL)
		return (NULL);
	ret = NULL;
	if (!(ret = (char *)ft_memalloc(len_strtrim(s) + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[i] && i < ft_strlen(s) - len_end(s))
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}
