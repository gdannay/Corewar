#include "corewar.h"

static int read_instruction(t_map *map, t_process **begin, t_process *process, int current)
{
	if (current == 1)
		return (instruction_live(map->vm, process, map->player));
  else if (current == 2)
		return (instruction_ld(map->vm, process));
  else if (current == 3)
  	return (instruction_st(map->vm, process));
	else if (current == 4)
	 	return (instruction_add(map->vm, process));
	else if (current == 5)
		return (instruction_sub(map->vm, process));
	else if (current == 6)
		return (instruction_and(map->vm, process));
	else if (current == 7)
		return (instruction_or(map->vm, process));
	else if (current == 8)
		return (instruction_xor(map->vm, process));
	else if (current == 9)
		return (instruction_zjmp(map->vm, process));
	else if (current == 10)
		return (instruction_ldi(map->vm, process));
	else if (current == 11)
		return (instruction_sti(map->vm, process));
	else if (current == 12)
		return (instruction_fork(map->vm, process, begin));
	else if (current == 13)
		return (instruction_lld(map->vm, process));
	else if (current == 14)
		return (instruction_lldi(map->vm, process));
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
	t_vm *vm;
	t_process	*tmp;
	int				ret;
	int				i;

	/*
	J'ai dissocié process de player parce que les instructions
	s’exécutent dans l’ordre décroissant des numéros de processus,
	et c'est trop compliqué de gérer l'ordre si les process sont
	stockés à plusieurs endroit différents et pas dans une liste
	chronologique de création.
	*/

	vm = map->vm;
	while (map->process && vm->cycle < 60)
	{
		printf("\n== Cycle: %ld ==\n", vm->cycle);
		tmp = map->process;
		i = 0;
		while (tmp)
		{
			tmp->position %= MEM_SIZE;
			printf("Nb process: %d\n", i);
			printf("Position: %d\n", tmp->position);
			if (tmp->inst)
				ret = read_instruction(map, &map->process, tmp, tmp->inst);
			else
				ret = read_instruction(map, &map->process, tmp, vm->arena[tmp->position]);
			if (!ret)
				return (0);
			i++;
			tmp = tmp->next;
			// Pour l'instant je parcours les process dans l'ordre croissant de creation, à changer plus tard en ordre decroissant
		}
		// A changer par la vraie condition d'arret avec CYCLE_TO_DIE
		vm->cycle++;
	}

	printf("\nRESULT\n");
	while (map->player)
	{
		printf("Player: %d -> nb live: %d\n", map->player->numero, map->player->global_live);
		map->player = map->player->next;
	}
	visu(vm->arena, map->player);
	return (1);
}
