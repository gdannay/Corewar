/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:58:07 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 18:20:40 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned	long	long	ft_it_power(int nb, int power)
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

char						*ft_lltoa_base(unsigned long long nb,
		int base, char c)
{
	char						*nbr;
	int							i;
	unsigned	long	long	ret;

	i = 1;
	if (base == 10)
		return (ft_lltoa(nb));
	if (nb == 0)
		return (ft_strdup("0"));
	while ((ret = ft_it_power(base, i)) <= nb)
	{
		if (ret == 0)
			break ;
		i++;
	}
	if (!(nbr = (char *)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	nbr[i + 1] = '\0';
	while (i-- != 0)
	{
		nbr[i] = (nb % base) + (nb % base > 9 ? c - 10 : '0');
		nb = nb / base;
	}
	return (nbr);
}
