/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:18:11 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 20:35:28 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

int		read_header(t_player **first, int fd, char *name)
{
	char	*buff;
	int		ret;
	int		*magic;
	char	*str;
	(void)first;
	(void)fd;
	if ((buff = (char *)ft_memalloc(sizeof(header_t))) == NULL)
		return (0);
	ret = read(fd, buff, sizeof(header_t));
	if (ret == -1)
	{
		dprintf(2, "A error occured while reading the file %s\n", name);
		return (0);
	}
	else if (ret < (int)sizeof(header_t))
	{
		dprintf(2, "Error: File %s is too small to be a champion\n", name);
		return (0);
	}
	magic = (int *)buff;
	if ((*magic = (int)swap_32_bytes(*magic)) != COREWAR_EXEC_MAGIC)
	{
		dprintf(2, "Error: File %s has an invalid header\n", name);
		return (0);
	}
	str = buff + 4;
	dprintf(1, "ICI = %s\n", str);	
	return (1);
}
