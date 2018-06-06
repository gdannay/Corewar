/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:35:38 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/06 14:10:38 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_players(t_player **first)
{
	t_player	*tmp;

	while (*first)
	{
		tmp = *first;
		*first = (*first)->next;
		if (tmp->header)
			free(tmp->header);
		ft_strdel(&(tmp->code));
		free(tmp);
	}
}

void	free_vm(t_vm **vm)
{
	ft_strdel(&(*vm)->arena);
	free(*vm);
}

void	free_process(t_process **process)
{
	t_process	*tmp;

	while (*process)
	{
		ft_bzero((*process)->registre, REG_NUMBER);
		tmp = *process;
		*process = (*process)->next;
		free(tmp);
	}
}

int		free_map(t_map *map)
{
	if (map)
	{
		if (map->player)
			free_players(&map->player);
		if (map->vm)
			free_vm(&map->vm);
		if (map->process)
			free_process(&map->process);
		free(map);
	}
	return (-1);
}
