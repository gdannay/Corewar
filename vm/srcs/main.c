/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:08:01 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/09 10:48:29 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

int		main(int ac, char **av)
{
	int 		fd;
	int 		i;
	char		*arena;
	t_player	*first;

	i = 0;
	first = NULL;
	arena = NULL;
	if (ac < 2)
	{
		dprintf(2, "Usage\n");
		return (-1);
	}
	while (++i < ac)
	{

		if ((fd = open(av[i], O_RDONLY)) == -1)
		{
			dprintf(2, "Can't read source file %s\n", av[i]);
			return (-1);
		}
		else if ((read_file(&first, fd, av[i])) == 0)
			return (-1);
		close (fd);
	}
	if (!(arena = create_arena(first)))
	{
		free_players(&first);
		return (-1);
	}
	visu(arena, first);
	ft_strdel(&arena);
	free_players(&first);
	return (0);
}
