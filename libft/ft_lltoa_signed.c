/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:47:11 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 18:26:08 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	long	long	len_malloc(long long n)
{
	long	long	len;

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

char					*ft_lltoa_signed(long long n)
{
	char			*ret;
	int				i;
	long	long	len;

	i = 0;
	len = len_malloc(n);
	if (!(ret = (char *)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n == 0)
		ret[i++] = '0';
	else if (n < 0)
	{
		if (n == -9223372036854775800 - 8)
			return (ft_strdup("-9223372036854775808"));
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
