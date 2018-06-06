/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:49:42 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/06 16:28:56 by clegirar         ###   ########.fr       */
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

void init_window_vm(WINDOW **arena, WINDOW **infos)
{
	init_window();
	*arena = subwin(stdscr, 66, 195, 0, 0);
	*infos = subwin(stdscr, 66, 100, 0, 197);
	box(*arena, ACS_VLINE, ACS_HLINE);
	box(*infos, ACS_VLINE, ACS_HLINE);
	wrefresh(*arena);
	wrefresh(*infos);
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
	t_player *player;
	t_process *process;
	int x;

	wattron(infos, COLOR_PAIR(1));
	if (map->space == 1)
		mvwprintw(infos, 1, 2, "***RUN***");
	else
		mvwprintw(infos, 1, 2, "**PAUSE**");
	wattroff(infos, COLOR_PAIR(1));

	mvwprintw(infos, 3, 2, "Cycle: %llu", map->vm->cycle);
	mvwprintw(infos, 4, 2, "Cycle to_die:     ");
	mvwprintw(infos, 4, 2, "Cycle to die: %d", map->vm->cycle_to_die);
	mvwprintw(infos, 5, 2, "Cycle delta: %d", map->vm->cycle_delta);
	mvwprintw(infos, 6, 2, "Max checks: %d", map->vm->max_checks);

	player = map->player;
	x = 8;
	while (player)
	{
		mvwprintw(infos, ++x, 2, "Player %d : %s", player->numero, player->header->prog_name);
		mvwprintw(infos, ++x, 2, " %-20s %d", "Last_live:", player->last_live);
		mvwprintw(infos, ++x, 2, " %-20s %d", "Global_live:", player->global_live);
		player = player->next;
	}
	process = map->process;
	x += 2;
	/*while (process)
	{
		mvwprintw(infos, ++x, 2, "Numero numero_who_create_process = %d have nb_live: %d", process->numero_who_create_process, process->live);
		process = process->next;
	}*/
	wrefresh(infos);
}

void display_windows_vm(WINDOW *arena, WINDOW *infos, t_map *map, int *get)
{
	print_infos(infos, map);
	print_arena(arena, map->vm, map->vm->arena, map);
	timeout(1);
	*get = getch();
	if (*get == ' ')
		map->space = (map->space) ? 0 : 1;
}
