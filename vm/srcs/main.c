/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:08:01 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/15 20:18:15 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int ac, char **av)
{
	t_map 		*map;
	t_player	*player;
	t_vm *vm;
	t_process *process;

	if (ac < 2)
	{
		dprintf(2, "Usage\n");
		return (-1);
	}
	if ((player = read_av(av, ac)) == NULL)
		return (-1);
	if ((vm = create_vm(player)) == NULL)
		return (-1);
	if (!(process = initialize_process(player)))
		return (-1);

	// Creation d'une map contenant les trois structures pour plus de lisibilité
	if (!(map = malloc(sizeof(t_map))))
		return (-1);

	map->player = player;
	map->vm = vm;
	map->process = process;

	if (!(run_vm(map)))
		return (-1);
//	visu(vm->arena, player);
	free_players(&player);
	return (0);
}
