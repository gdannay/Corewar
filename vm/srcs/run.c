#include "corewar.h"

static void read_instruction(t_machine *machine, t_process *process, t_player *player)
{
	if (machine->arena[process->position] == 1)
		process->position += instruction_live(machine, process, player);
  else if (machine->arena[process->position] == 2)
		process->position += instruction_ld(machine, process);
  else if (machine->arena[process->position] == 3)
  	process->position += instruction_st(machine, process);
	else
	{
		printf("Not instruction\n");
		process->position++;
	}
}

void run_vm(t_map *map)
{
	t_machine *machine;
	t_process *process;

	machine = map->machine;
	while (1)
	{
		printf("\nCycle: %ld\n", machine->cycle);
		process = map->process;
		while (process)
		{
			process->position %= MEM_SIZE;
			printf("Position: %d\n", process->position);
			read_instruction(machine, process, map->player);
			process = process->next;
      break;
		}
		// A changer par la vraie condition d'arret
		if (machine->cycle == 15)
			break ;
		machine->cycle++;
	}

//  visu(machine->arena, map->player);
	printf("\nRESULT\n");
	while (map->player)
	{
		printf("Player: %d -> nb live: %d\n", map->player->numero, map->player->global_live);
		map->player = map->player->next;
	}
}
