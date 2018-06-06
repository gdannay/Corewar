/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <vferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:45:14 by vferreir          #+#    #+#             */
/*   Updated: 2018/06/06 16:28:49 by clegirar         ###   ########.fr       */
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
		process->position++;
	}
	else
		process->position++;
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

int				condition_arret(t_map *map, int get)
{
	t_process	*process;

	//printf("%llu\n", map->vm->cycle);
	process = map->process;
	if (map->vm->cycle_to_die <= 0)
	{
		while (process)
		{
			map->vm->nbr_live += process->live;
			if (process->live == 0)
				kill_process(&process, map);
			else
			{
				process->live = 0;
				process = process->next;
			}
		}
		if (!(map->flag & V_FLAG) || map->space || get == 's')
		{
			if (map->vm->nbr_live >= NBR_LIVE || map->vm->max_checks == 10)
			{
				map->vm->cycle_delta += CYCLE_DELTA;
				map->vm->max_checks = 0;
			}
			else
				map->vm->max_checks++;
			map->vm->cycle_to_die = CYCLE_TO_DIE;
		}
	}
	if (!map->process)
		return (0);
	if (!(map->flag & V_FLAG) || map->space || get == 's')
	{
		map->vm->cycle_to_die--;
		map->vm->cycle++;
	}
	return (1);
}

int				run_vm(t_map *map)
{
	WINDOW		*arena;
	WINDOW		*infos;
	t_process	*tmp;
	int				ret;
	int				i;
	int				get;

	map->vm->cycle_to_die = CYCLE_TO_DIE;
	map->vm->nbr_live = 0;
	map->vm->cycle_delta = 0;
	map->vm->max_checks = 0;
	if (map->flag & V_FLAG)
		init_window_vm(&arena, &infos);
	get = 0;
	while (condition_arret(map, get))// && map->vm->cycle < 2050)
	{
		printf("\nCYCLE = %llu\n", map->vm->cycle);
		tmp = map->process;
		i = 1;
		while (tmp)
		{
			tmp->position %= MEM_SIZE;
//			printf("POS = %d\n", tmp->position);
			if (tmp->inst && (!(map->flag & V_FLAG) || map->space || get == 's'))
				ret = read_instruction(map, &map->process, tmp, tmp->inst);
			else if (!(map->flag & V_FLAG) || map->space || get == 's')
				ret = read_instruction(map, &map->process,
						tmp, map->vm->arena[tmp->position]);
			if (!ret)
				return (0);
			i++;
			tmp = tmp->next;
		}
		if (map->flag & V_FLAG)
			display_windows_vm(arena, infos, map, &get);
		else
			map->vm->cycle++;
	}
	if (map->flag & V_FLAG)
		endwin();
	return (1);
}
