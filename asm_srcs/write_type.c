/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:30:32 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/28 13:34:20 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern struct s_op op_tab[17];

int	write_registre(int fd, char *param)
{
	char	nb;

	nb = ft_atoi(param + 1);
	if ((write(fd, &nb, 1)) < 0)
		return (ERROR);
	return (TRUE);
}

int	write_direct(t_inst *first, int fd, char *param)
{
	int nb;

	nb = ft_atoi(param + 1);
	if (op_tab[first->code].unknown == 1)
	{
		nb = swap_16_bytes(nb);
		if ((write(fd, &nb, 2)) < 0)
			return (ERROR);
	}
	else
	{
		nb = swap_32_bytes(nb);
		if ((write(fd, &nb, 4)) < 0)
			return (ERROR);
	}
	return (TRUE);
}

int	write_indirect(int fd, char *param)
{
	int nb;

	nb = ft_atoi(param);
	nb = swap_16_bytes(nb);
	if ((write(fd, &nb, 2)) < 0)
		return (ERROR);
	return (TRUE);
}
