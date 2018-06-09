/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <vferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:59:01 by vferreir          #+#    #+#             */
/*   Updated: 2018/06/09 15:24:25 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			recup_nb_32(char *arena, int position)
{
	int nb;

	position %= MEM_SIZE;
	if (position < 0)
		position += MEM_SIZE;
	nb = (unsigned char)arena[(position + 3) % MEM_SIZE]
		| (unsigned char)arena[(position + 2) % MEM_SIZE] << 8
		| (unsigned char)arena[(position + 1) % MEM_SIZE] << 16
		| (unsigned char)arena[(position) % MEM_SIZE] << 24;
	return (nb);
}

int			recup_nb_16(char *arena, int position)
{
	int nb;

	position %= MEM_SIZE;
	if (position < 0)
		position += MEM_SIZE;
	nb = (unsigned char)arena[(position + 1) % MEM_SIZE]
		| (unsigned char)arena[(position) % MEM_SIZE] << 8;
	return (nb);
}

void		write_in_arena_32(t_vm *vm, int registre, int pos, int nb)
{
	pos %= MEM_SIZE;
	if (pos < 0)
		pos += MEM_SIZE;
	vm->arena[pos % MEM_SIZE] = registre >> 24;
	vm->arena[(pos + 1) % MEM_SIZE] = registre >> 16;
	vm->arena[(pos + 2) % MEM_SIZE] = registre >> 8;
	vm->arena[(pos + 3) % MEM_SIZE] = registre;
	vm->arena_player[pos % MEM_SIZE] = nb;
	vm->arena_player[(pos + 1) % MEM_SIZE] = nb;
	vm->arena_player[(pos + 2) % MEM_SIZE] = nb;
	vm->arena_player[(pos + 3) % MEM_SIZE] = nb;
}

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

void		print_result(t_map *map)
{
	t_player	*player;
	char		*name;
	int			last_live;

	last_live = 0;
	name = NULL;
	player = map->player;
	while (player)
	{
		if (player->last_live > last_live)
		{
			last_live = player->last_live;
			name = player->header->prog_name;
		}
		player = player->next;
	}
	if (name != NULL)
		ft_printf("Contestant 1, \"%s\", has won !\n", name);
	else
		ft_printf("It's a game with no winner\n");
}
