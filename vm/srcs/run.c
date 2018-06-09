/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <vferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:45:14 by vferreir          #+#    #+#             */
/*   Updated: 2018/06/08 17:30:53 by clegirar         ###   ########.fr       */
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

static	int		read_inst(t_map *map, t_process **begin,
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
	map->vm->process--;
}

static	void	check_visu_infos(t_map *map, int get)
{
	if (!(map->flag & V_FLAG) || map->space || get == 's')
	{
		if (map->vm->nbr_live >= NBR_LIVE || map->vm->max_checks == 10)
		{
			map->vm->cycle_delta += CYCLE_DELTA;
			map->vm->max_checks = 0;
		}
		else
			map->vm->max_checks++;
		map->vm->cycle_to_die = CYCLE_TO_DIE - map->vm->cycle_delta;
	}
	map->vm->nbr_live = 0;
}

int				condition_arret(t_map *map, int get, t_process *process)
{
	if (map->vm->cycle >= map->dump)
		return (0);
	if (map->vm->cycle_to_die <= 0)
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
		check_visu_infos(map, get);
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

int				run_vm(t_map *map, int ret, int get, t_process *tmp)
{
	if (map->flag & V_FLAG)
		init_window_vm(&map->vm->arena_w, &map->vm->infos);
	while (condition_arret(map, get, map->process))
	{
		tmp = map->process;
		while (tmp)
		{
			tmp->position %= MEM_SIZE;
			if (tmp->inst
					&& (!(map->flag & V_FLAG) || map->space || get == 's'))
				ret = read_inst(map, &map->process, tmp, tmp->inst);
			else if (!(map->flag & V_FLAG) || map->space || get == 's')
				ret = read_inst(map, &map->process,
						tmp, map->vm->arena[tmp->position]);
			if (!ret)
				return (0);
			tmp = tmp->next;
		}
		(map->flag & V_FLAG) ? display_windows_vm(map->vm->arena_w,
			map->vm->infos, map, &get) : map->vm->cycle++;
	}
	(map->flag & V_FLAG) ? endwin() : 0;
	print_result(map);
	return (1);
}
