/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:49:42 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/08 17:14:54 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	int		check_pos_process(t_process *process, int i)
{
	t_process	*tmp;

	tmp = process;
	while (tmp)
	{
		if (i == tmp->position)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static	void	print_case_arena(t_map *map, int y, int x, int i)
{
	char	line[3];

	line[2] = 0;
	line[1] = (unsigned char)map->vm->arena[i] % 16;
	line[0] = ((unsigned char)map->vm->arena[i] / 16) % 16;
	line[0] += (line[0] >= 10) ? ('a' - 10) : ('0');
	line[1] += (line[1] >= 10) ? ('a' - 10) : ('0');
	wattron(map->vm->arena_w, COLOR_PAIR(map->vm->arena_player[i]));
	if (check_pos_process(map->process, i))
	{
		mvwaddch(map->vm->arena_w, y, x, line[0] | A_REVERSE);
		mvwaddch(map->vm->arena_w, y, x + 1, line[1] | A_REVERSE);
	}
	else
	{
		mvwaddch(map->vm->arena_w, y, x, line[0]);
		mvwaddch(map->vm->arena_w, y, x + 1, line[1]);
	}
	wattroff(map->vm->arena_w, COLOR_PAIR(map->vm->arena_player[i]));
}

void			print_arena(WINDOW *visu, t_vm *vm, char *arena, t_map *map)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 2;
	y = 1;
	while (i < MEM_SIZE)
	{
		print_case_arena(map, y, x, i);
		i++;
		x = (i != 0 && i % 64 == 0) ? 2 : x + 3;
		(i != 0 && i % 64 == 0) ? y += 1 : 0;
	}
	wrefresh(visu);
}

void			print_infos(WINDOW *infos, t_map *map)
{
	t_player	*player;
	int			x;

	wattron(infos, COLOR_PAIR(1));
	(map->space) ? mvwprintw(infos, 1, 2, "***RUN***")
	: mvwprintw(infos, 1, 2, "**PAUSE**");
	wattroff(infos, COLOR_PAIR(1));
	mvwprintw(infos, 3, 2, "Cycle: %llu", map->vm->cycle);
	mvwprintw(infos, 4, 2, "Cycle to_die:     ");
	mvwprintw(infos, 4, 2, "Cycle to die: %d",
			map->vm->cycle_to_die);
	mvwprintw(infos, 5, 2, "Cycle delta: %d", map->vm->cycle_delta);
	mvwprintw(infos, 6, 2, "Max checks: %d", map->vm->max_checks);
	mvwprintw(infos, 7, 2, "Nbr_live: %d", map->vm->nbr_live);
	player = map->player;
	x = 8;
	while (player)
	{
		wattron(infos, COLOR_PAIR(player->color));
		mvwprintw(infos, ++x, 2, "Player %d : %s",
				player->numero, player->header->prog_name);
		wattroff(infos, COLOR_PAIR(player->color));
		mvwprintw(infos, ++x, 2, " %-20s %d", "Last_live:", player->last_live);
		mvwprintw(infos, ++x, 2, " %-20s %d", "Global_live:",
				player->global_live);
		player = player->next;
	}
	mvwprintw(infos, x + 2, 2, "Number process: %d", map->vm->process);
	wrefresh(infos);
}

void			display_windows_vm(WINDOW *arena, WINDOW *infos,
		t_map *map, int *get)
{
	print_infos(infos, map);
	print_arena(arena, map->vm, map->vm->arena, map);
	timeout(1);
	*get = getch();
	if (*get == ' ')
		map->space = (map->space) ? 0 : 1;
}
