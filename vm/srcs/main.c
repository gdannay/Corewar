/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:08:01 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/21 11:39:47 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int ac, char **av)
{
	t_map 		*map;

	if (ac < 2)
	{
		dprintf(2, "Usage\n");
		return (-1);
	}
	if ((!(map = malloc(sizeof(t_map))))
	|| ((map->player = read_av(av, ac)) == NULL)
	|| ((map->vm = create_vm(map->player)) == NULL)
	|| (!(map->process = initialize_process(map->player))))
		return (-1);
	if (!(run_vm(map)))
		return (-1);
	free_players(&map->player);
	return (0);
}
