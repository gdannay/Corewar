/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:08:01 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 19:39:20 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int ac, char **av)
{
	int 		fd;
	int 		i;
	t_player	*first;

	i = 0;
	first = NULL;
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
		else if ((read_header(&first, fd, av[i])) == 0)
			return (-1);
	}
	return (0);
}
