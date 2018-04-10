/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 12:43:25 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/03 14:15:02 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puttab_int(int **tab)
{
	int	i;
	int	j;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			ft_putnbr(tab[i][j]);
			ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
