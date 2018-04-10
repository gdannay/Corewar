/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:47:11 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 18:18:51 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	len_malloc(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		len++;
	else if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*ret;
	int		i;
	int		len;

	i = 0;
	len = len_malloc(n);
	if (!(ret = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n == 0)
		ret[i++] = '0';
	else if (n < 0)
	{
		n = n * -1;
		ret[i++] = '-';
	}
	while (n > 0)
	{
		ret[--len] = n % 10 + '0';
		i++;
		n = n / 10;
	}
	ret[i] = '\0';
	return (ret);
}
