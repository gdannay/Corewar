/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:08:01 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/28 16:12:12 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int ac, char **av)
{
	t_map	*map;

	if (ac < 2)
	{
		dprintf(2, "Usage\n");
		return (-1);
	}
	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		return (-1);
	map->space = 0;
	map->player = NULL;
	map->vm = NULL;
	map->process = NULL;
	if ((!(map->player = read_av(av, ac)))
			|| (!(map->vm = create_vm(map->player)))
			|| (!(map->process = initialize_process(map->player)))
			|| (!(run_vm(map))))
		return (free_map(map));
	free_map(map);
	return (0);
}
