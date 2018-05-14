#include "corewar.h"

static void read_instruction(t_vm *vm, t_process *process, t_player *player, int current)
{
	if (current == 1)
		process->position += instruction_live(vm, process, player);
  else if (current == 2)
		process->position += instruction_ld(vm, process);
  else if (current == 3)
  	process->position += instruction_st(vm, process);
	else if (current == 4)
	 	process->position += instruction_add(vm, process);
	else if (current == 5)
		process->position += instruction_sub(vm, process);
	else if (current == 6)
		process->position += instruction_and(vm, process);
	else if (current == 7)
		process->position += instruction_or(vm, process);
	else if (current == 8)
		process->position += instruction_xor(vm, process);
	else if (current == 9)
		process->position += instruction_zjmp(vm, process);
	else if (current == 10)
		process->position += instruction_ldi(vm, process);
	else
	{
		printf("Not instruction\n");
		process->position++;
	}
}

void run_vm(t_map *map)
{
	t_vm *vm;
	t_process *process;

	/*
	J'ai dissocié process de player parce que les instructions
	s’exécutent dans l’ordre décroissant des numéros de processus,
	et c'est trop compliqué de gérer l'ordre si les process sont
	stockés à plusieurs endroit différents et pas dans une liste
	chronologique de création.
	*/

	vm = map->vm;
	while (1)
	{
		printf("\n== Cycle: %ld ==\n", vm->cycle);
		process = map->process;
		while (process)
		{
			process->position %= MEM_SIZE;
			printf("Position: %d\n", process->position);
			if (process->inst)
				read_instruction(vm, process, map->player, process->inst);
			else
				read_instruction(vm, process, map->player, vm->arena[process->position]);

			// Pour l'instant je parcours les process dans l'ordre croissant de creation, à changer plus tard en ordre decroissant
			process = process->next;
      break;
		}
		// A changer par la vraie condition d'arret avec CYCLE_TO_DIE
		if (vm->cycle == 40)
			break ;
		vm->cycle++;
	}

	printf("\nRESULT\n");
	while (map->player)
	{
		printf("Player: %d -> nb live: %d\n", map->player->numero, map->player->global_live);
		map->player = map->player->next;
	}
	visu(vm->arena, map->player);
}
