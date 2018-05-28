/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <vferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:45:14 by vferreir          #+#    #+#             */
/*   Updated: 2018/05/28 14:25:55 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	t_ptr	g_ptr[] =
{
	{2, &instruction_ld},
	{3, &instruction_st},
	{4, &instruction_add},
	{5, &instruction_sub},
	{6, &instruction_and},
	{7, &instruction_or},
	{8, &instruction_xor},
	{9, &instruction_zjmp},
	{10, &instruction_ldi},
	{11, &instruction_sti},
	{13, &instruction_lld},
	{14, &instruction_lldi},
	{16, &instruction_aff}
};

static	int		read_instruction(t_map *map, t_process **begin,
		t_process *process, int current)
{
	int		i;

	i = 0;
	if (current == 1)
		return (instruction_live(map->vm, process, map->player));
	else if (current == 12)
		return (instruction_fork(map->vm, process, begin));
	else if (current == 15)
		return (instruction_lfork(map->vm, process, begin));
	else if (current)
	{
		while (g_ptr[i].current)
		{
			if (current == g_ptr[i].current)
				return (g_ptr[i].f(map->vm, process));
			i++;
		}
	}
	else
	{
		//printf("Not instruction\n");
		process->position++;
	}
	return (1);
}

void			print_process(t_process *process)
{
	t_process	*tmp;
	int			i;

	i = 1;
	tmp = process;
	while (tmp)
	{
		printf("%d\n", i);
		i++;
		tmp = tmp->next;
	}
}

void			kill_process(t_process **process, t_map *map)
{
	t_process	*tmp;

	if (*process && !(*process)->prev)
	{
		tmp = (*process);
		map->process = (*process)->next;
		(*process) = (*process)->next;
		if (*process)
			(*process)->prev = NULL;
		free(tmp);
	}
	else
	{
		tmp = (*process);
		(*process) = (*process)->next;
		tmp->prev->next = (*process);
		if (*process)
			(*process)->prev = tmp->prev;
		free(tmp);
	}
}

int				condition_arret(t_map *map)
{
	t_process	*process;

	//printf("%llu\n", map->vm->cycle);
	process = map->process;
	if (!map->vm->cycle_to_die)
	{
		while (process)
		{
			if (process->live == 0)
				kill_process(&process, map);
			else
			{
				process->live = 0;
				process = process->next;
			}
		}
		map->vm->cycle_to_die = CYCLE_TO_DIE - map->vm->cycle_delta;
		map->vm->cycle_delta += CYCLE_DELTA;
	}
	if (!map->process)
		return (0);
	map->vm->cycle_to_die--;
	return (1);
}

int				run_vm(t_map *map)
{
	WINDOW		*arena;
	WINDOW		*infos;
	t_process	*tmp;
	int				ret;
	int				i;

	init_window();
	arena = subwin(stdscr, 66, 195, 0, 0);
	infos = subwin(stdscr, 66, 100, 0, 197);
	box(arena, ACS_VLINE, ACS_HLINE);
	box(infos, ACS_VLINE, ACS_HLINE);
  wrefresh(arena);
	wrefresh(infos);
	while (condition_arret(map))
	{
		tmp = map->process;
		i = 0;
		mvwprintw(infos, 1, 1, "== Cycle: %llu, cycle_to_die = %d, cycle_delta = %d ==", map->vm->cycle, map->vm->cycle_to_die, map->vm->cycle_delta);
		wrefresh(infos);
		while (tmp)
		{
			tmp->position %= MEM_SIZE;
			//printf("Nb process: %d\n", i);
			//printf("Position: %d\n", tmp->position);
			/*mvprintw(10, 1800, "Nb process: %d\n", i);
			  refresh();
			  mvprintw(20, 1800, "Position: %d\n", tmp->position);
			  refresh();*/
			if (tmp->inst)
				ret = read_instruction(map, &map->process, tmp, tmp->inst);
			else
				ret = read_instruction(map, &map->process,
						tmp, map->vm->arena[tmp->position]);
			if (!ret)
				return (0);
			i++;
			tmp = tmp->next;
		}
		print_arena(arena, map->vm, map->vm->arena);
		map->vm->cycle++;
	}
	endwin();
	printf("\nRESULT\n");
	while (map->player)
	{
		printf("Player: %d -> nb live: %d\n",
				map->player->numero, map->player->global_live);
		map->player = map->player->next;
	}
	return (1);
}
