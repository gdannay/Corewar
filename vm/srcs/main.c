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

int recup_int(char *str)
{
	int nb;

	nb = (unsigned char)str[3]
				| (unsigned char)str[2] << 8
				| (unsigned char)str[1] << 16
				| (unsigned char)str[0] << 24;
	return (nb);
}

int function_live(t_machine *machine, t_player *first, char *str)
{
	int nb;

	nb = recup_int(str + 1);
	printf("Value: %d\n", nb);

	while (first)
	{
		printf("");
	}

	(void)first;
	(void)machine;
	return (5);
}

void test_vince(t_machine *machine, t_player *first)
{
	int process;

	process = 0;
	printf("Processus: %02hhx\n", machine->arena[process]);
	if (machine->arena[process] == 1)
		process += function_live(machine, first, machine->arena + process);
}

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

t_machine *create_machine(t_player *first)
{
	t_machine *machine;

	if (!(machine = (t_machine *)ft_memalloc(sizeof(t_machine))))
		return (NULL);
	if (!(machine->arena = create_arena(first)))
	{
		free_players(&first);
		return (NULL);
	}
	machine->cycle = 0;
	machine->cycle_to_die = 0;
	machine->cycle_delta = 0;
	machine->nbr_live = 0;
	machine->process = 0;
	return (machine);
}


int		main(int ac, char **av)
{
	t_player	*first;
	t_machine *machine;

	if (ac < 2)
	{
		dprintf(2, "Usage\n");
		return (-1);
	}
	if ((first = read_av(av, ac)) == NULL)
		return (-1);
	if ((machine = create_machine(first)) == NULL)
		return (-1);
	test_vince(machine, first);
//	visu(machine->arena, first);
	free_players(&first);
	return (0);
}
