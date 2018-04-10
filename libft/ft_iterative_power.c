/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 13:49:20 by clegirar          #+#    #+#             */
/*   Updated: 2017/07/09 16:14:53 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iterative_power(int nb, int power)
{
	int		result;

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
