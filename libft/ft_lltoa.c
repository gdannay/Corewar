/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:47:11 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 18:32:31 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	len_malloc(unsigned long long n)
{
	int	len;

	len = 0;
	if (n == 0)
		len++;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_lltoa(unsigned long long n)
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
	while (n > 0)
	{
		ret[--len] = n % 10 + '0';
		i++;
		n = n / 10;
	}
	ret[i] = '\0';
	return (ret);
}
