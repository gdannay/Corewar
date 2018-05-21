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
	{14, &instruction_lldi}
};

static int read_instruction(t_map *map, t_process **begin, t_process *process,
	int current)
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
		printf("Not instruction\n");
		process->position++;
	}
	return (1);
}

void 	print_process(t_process *process)
{
	t_process	*tmp;
	int		i = 1;

	tmp = process;
	while (tmp)
	{
		printf("%d\n", i);
		i++;
		tmp = tmp->next;
	}
}

int run_vm(t_map *map)
{
	t_process	*tmp;
	int				ret;
	int				i;

	//init_window();
	while (map->process && map->vm->cycle < 38)
	{
		tmp = map->process;
		i = 0;
		while (tmp)
		{
			tmp->position %= MEM_SIZE;
			printf("Nb process: %d\n", i);
			printf("Position: %d\n", tmp->position);
			/*mvprintw(10, 1800, "Nb process: %d\n", i);
			refresh();
			mvprintw(20, 1800, "Position: %d\n", tmp->position);
			refresh();*/
			if (tmp->inst)
				ret = read_instruction(map, &map->process, tmp, tmp->inst);
			else
				ret = read_instruction(map, &map->process, tmp, map->vm->arena[tmp->position]);
			if (!ret)
				return (0);
			i++;
			tmp = tmp->next;
		}
		//print_arena(map->vm, map->vm->arena);
		/*printw("\n== Cycle: %ld ==\n", vm->cycle);
		refresh();*/
		printf("\n== Cycle: %ld ==\n", map->vm->cycle);
		map->vm->cycle++;
	}
	//print_arena(map->vm, map->vm->arena);
	//endwin();
	printf("\nRESULT\n");
	while (map->player)
	{
		printf("Player: %d -> nb live: %d\n", map->player->numero, map->player->global_live);
		map->player = map->player->next;
	}
	return (1);
}
