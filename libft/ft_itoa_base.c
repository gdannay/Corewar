/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:58:07 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 18:25:45 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned int nb, int base, char c)
{
	char			*nbr;
	int				i;
	unsigned	int	ret;

	i = 1;
	if (nb == 0)
		return (ft_strdup("0"));
	while ((ret = ft_iterative_power(base, i)) <= nb)
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
