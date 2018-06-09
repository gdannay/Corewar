/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 16:11:29 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/08 17:39:07 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	int		nbr_players(t_player *first)
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

static	void	copy_code(char *arena, char *code, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		arena[i] = code[i];
}

static	void	copy_nb_player(char *arena, int numero, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		arena[i] = numero;
}

static	int		create_arenas(t_vm **vm, t_player *first)
{
	int			i;
	t_player	*tmp;

	if ((!((*vm)->arena = (char *)ft_memalloc(sizeof(char) * MEM_SIZE)))
		|| (!((*vm)->arena_player =
				(char *)ft_memalloc(sizeof(char) * MEM_SIZE))))
		return (0);
	i = 0;
	(*vm)->nbr_players = nbr_players(first);
	(*vm)->ecart = MEM_SIZE / (*vm)->nbr_players;
	tmp = first;
	while (tmp)
	{
		copy_code((*vm)->arena + i * (*vm)->ecart, tmp->code,
				(int)swap_32_bytes(tmp->header->prog_size));
		copy_nb_player((*vm)->arena_player + i * (*vm)->ecart, tmp->color,
				(int)swap_32_bytes(tmp->header->prog_size));
		tmp->start = i * (*vm)->ecart;
		tmp = tmp->next;
		i++;
	}
	return (1);
}

t_vm			*create_vm(t_player *first)
{
	t_vm	*vm;

	if ((!(vm = (t_vm *)ft_memalloc(sizeof(t_vm))))
		|| (!(create_arenas(&vm, first))))
		return (NULL);
	vm->process = vm->nbr_players;
	vm->max_checks = 0;
	vm->cycle = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_delta = 0;
	vm->nbr_live = 0;
	return (vm);
}
