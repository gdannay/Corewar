/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entry_result.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:16:13 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/11 17:16:31 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_entry(t_map *map)
{
	t_player	*tmp;

	tmp = map->player;
	ft_printf("Introducing contestants...\n");
	while (tmp)
	{
		ft_printf("* Player %d, weighing %ld bytes, \"%s\" (\"%s\") !\n",
				tmp->numero * -1, (int)swap_32_bytes(tmp->header->prog_size),
				tmp->header->prog_name, tmp->header->comment);
		tmp = tmp->next;
	}
}

void		print_result(t_map *map)
{
	t_player	*player;
	char		*name;
	int			last_live;

	if (map->process)
		return ;
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
