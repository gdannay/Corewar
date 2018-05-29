/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:49:42 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/29 18:34:54 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 		init_window(void)
{
	initscr();
	noecho();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	clear();
	curs_set(FALSE);
}

static	int	check_pos_process(t_process *process, int i)
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

void 		print_arena(WINDOW *visu, t_vm *vm, char *arena, t_map *map)
{
	int	i;
	int	x;
	int	y;
	char		line[3];

	(void)vm;
	(void)map;
	i = 0;
	x = 2;
	y = 1;
	while (i < MEM_SIZE)
	{
		//mvwprintw(visu, y, x, "%02hhx", arena[i]);
		line[2] = 0;
		line[1] = (unsigned char)arena[i] % 16;
		line[0] = ((unsigned char)arena[i] / 16) % 16;
		line[0] += (line[0] >= 10) ? ('a' - 10) : ('0');
		line[1] += (line[1] >= 10) ? ('a' - 10) : ('0');
		wattron(visu, COLOR_PAIR(vm->arena_player[i]));
		if (check_pos_process(map->process, i))
		{
			mvwaddch(visu, y, x, line[0] | A_REVERSE);
			mvwaddch(visu, y, x + 1, line[1] | A_REVERSE);
		}
		else
		{
			mvwaddch(visu, y, x, line[0]);
			mvwaddch(visu, y, x + 1, line[1]);
		}
		wattroff(visu, COLOR_PAIR(vm->arena_player[i]));
		i++;
		if (i != 0 && i % 64 == 0)
		{
			x = 2;
			y += 1;
		}
		else
			x += 3;
	}
	wrefresh(visu);
}

void 		print_infos(WINDOW *infos, t_map *map)
{
	mvwprintw(infos, 1, 2, "== Cycle: %llu, cycle_to_die = %d, cycle_delta = %d ==", map->vm->cycle, map->vm->cycle_to_die, map->vm->cycle_delta);
}
