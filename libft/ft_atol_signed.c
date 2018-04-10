/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:42:26 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 18:19:59 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	long	ft_atol_signed(const char *str)
{
	long	long	res;
	int				i;
	int				sign;

	res = 0;
	i = 0;
	sign = 1;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0') * sign;
		i++;
	}
	return (res);
}
