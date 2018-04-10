/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:43:31 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 18:20:23 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned	long	long	ft_it_power(int nb, int power)
{
	unsigned	long	long	result;

	result = 1;
	if (power < 0)
		return (0);
	while (power > 0)
	{
		result = result * nb;
		power--;
	}
	return (result);
}

unsigned	long	long			ft_atoll_base(char *str, int base, char c)
{
	unsigned	long	long	nbl;
	int							i;
	int							val;

	i = 0;
	nbl = 0;
	val = (int)ft_strlen(str) - 1;
	while (str[i])
	{
		nbl = nbl + ((str[i] > '9' ? str[i] - c + 10 : str[i] - '0')
				* ft_it_power(base, val));
		val--;
		i++;
	}
	return (nbl);
}
