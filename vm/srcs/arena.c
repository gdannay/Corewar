/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:11:29 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/09 11:10:56 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	nbr_players(t_player *first)
{
	int			i;
	t_player	*tmp;

	i = 0;
	tmp = first;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static void	copy_code(char *arena, char *code, int size)
{
	int i;

	i = -1;
	while (++i < size)
		arena[i] = code[i];
}

char		*create_arena(t_player *first)
{
	char		*arena;
	int			space;
	int			i;
	int			nbr;
	t_player	*tmp;

	if (!(arena = (char *)ft_memalloc(sizeof(char) * (MEM_SIZE))))
		return (NULL);
	i = 0;
	nbr = nbr_players(first);
	space = MEM_SIZE / nbr;
	tmp = first;
	while (tmp)
	{
		copy_code(arena + i * space, tmp->code, (int)swap_32_bytes(tmp->header->prog_size));
		tmp = tmp->next;
		i++;
	}
	return (arena);
}

t_vm *create_vm(t_player *first)
{
	t_vm *vm;

	if (!(vm = (t_vm *)ft_memalloc(sizeof(t_vm))))
		return (NULL);
	if (!(vm->arena = create_arena(first)))
	{
		free_players(&first);
		return (NULL);
	}
	vm->cycle = 0;
	vm->cycle_to_die = 0;
	vm->cycle_delta = 0;
	vm->nbr_live = 0;
	vm->process = 0;
	return (vm);
}
