#include "corewar.h"

int instruction_live(t_vm *vm, t_process *process, t_player *player)
{
	int numero_live;

	printf("LIVE --> ");
	if (process->cycle + 1 < 10)
	{
		process->inst = 1;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	numero_live = recup_nb_32(vm->arena, process->position + 1);
	while (player)
	{
		if (player->numero == numero_live)
			player->global_live++;
		player = player->next;
	}
	printf("Done\n");
	process->cycle = 0;
	process->inst = 0;
	process->position += 5;
	return (1);
}

int instruction_ld(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("LD --> ");
	if (process->cycle + 1 < 5)
	{
		process->inst = 2;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + (params[0] % IDX_MOD));
	if (params[1] && params[1] >= 1 && params[1] <= 16)
		process->registre[params[1] - 1] = params[0];
	if (!params[0])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_st(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("ST --> ");
	if (process->cycle + 1 < 5)
	{
		process->inst = 3;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[1] && str[1] == 'r' && params[1] && params[1] >= 1 && params[1] <= 16
	&& params[0] && params[0] >= 1 && params[0] <= 16)
		process->registre[params[1] - 1] = process->registre[params[0] - 1];
	else if (params[0] && params[0] >= 1 && params[0] <= 16)
		write_in_arena_32(vm->arena, process->registre[params[0] - 1], process->position + (params[1] % IDX_MOD));
	if (!params[0])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_add(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("ADD --> ");
	if (process->cycle + 1 < 10)
	{
		process->inst = 4;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (params[0] && params[0] >= 1 && params[0] <= 16
		&& params[1] && params[1] >= 1 && params[1] <= 16
		&& params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = process->registre[params[0] - 1] + process->registre[params[1] - 1];
	if (!process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_sub(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("SUB --> ");
	if (process->cycle + 1 < 10)
	{
		process->inst = 5;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (params[0] && params[0] >= 1 && params[0] <= 16
		&& params[1] && params[1] >= 1 && params[1] <= 16
		&& params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = process->registre[params[0] - 1] - process->registre[params[1] - 1];
	if (params[2] && params[2] >= 1 && params[2] <= 16 && !process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_and(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("AND --> ");
	if (process->cycle + 1 < 6)
	{
		process->inst = 6;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'r' && params[0] && params[0] >= 1 && params[0] <= 16)
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r' && params[1] && params[1] >= 1 && params[1] <= 16)
		params[1] = process->registre[params[1] - 1];
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + (params[0] % IDX_MOD));
	if (str[1] && str[1] == 'i')
		params[1] = recup_nb_32(vm->arena, process->position + (params[1] % IDX_MOD));
	printf("%d, %d\n", params[0], params[1]);
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = params[0] & params[1];
	if (!process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_or(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("OR --> ");
	if (process->cycle + 1 < 6)
	{
		process->inst = 7;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + (params[0] % IDX_MOD));
	if (str[1] && str[1] == 'i')
		params[1] = recup_nb_32(vm->arena, process->position + (params[1] % IDX_MOD));
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = params[0] | params[1];
	if (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_xor(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("XOR --> ");
	if (process->cycle + 1 < 6)
	{
		process->inst = 8;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = params[0] ^ params[1];
	if (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_zjmp(t_vm *vm, t_process *process)
{
	printf("ZJMP --> ");
	if (process->cycle + 1 < 20)
	{
		process->inst = 9;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	process->cycle = 0;
	process->inst = 0;
	if (process->carry == 0)
		process->position += 3;
	else
		process->position += recup_nb_16(vm->arena, process->position + 1);
	printf(" Done\n");
	return (1);
}

int instruction_ldi(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("LDI --> ");
	if (process->cycle + 1 < 25)
	{
		process->inst = 10;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 1);
	if (str[0] && str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + (params[0] % IDX_MOD));
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] =
		recup_nb_32(vm->arena, process->position + params[0] + params[1]);
	if (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_sti(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("STI --> ");
	if (process->cycle + 1 < 25)
	{
		process->inst = 11;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 1);
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (str[2] && str[2] == 'r')
		params[2] = process->registre[params[2] - 1];
	if (str[1] && str[1] == 'i')
		params[1] = recup_nb_32(vm->arena, process->position + (params[1] % IDX_MOD));
	if (params[0] && params[0] >= 1 && params[0] <= 16)
		write_in_arena_32(vm->arena, process->registre[params[0] - 1], process->position + ((params[1] % IDX_MOD) + (params[2] % IDX_MOD)));
	if (params[0] && params[0] >= 1 && params[0] <= 16
		&& !process->registre[params[0] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_fork(t_vm *vm, t_process *process, t_process **begin)
{
	printf("FORK --> ");
	if (process->cycle + 1 < 800)
	{
		process->inst = 12;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(create_new_process(begin, process, process->position + (recup_nb_16(vm->arena, process->position + 1) % IDX_MOD), process->numero_who_create_process)))
		return (0);
	process->cycle = 0;
	process->inst = 0;
	process->position += 3;
	printf(" Done\n");
	return (1);
}

int instruction_lld(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("LLD --> ");
	if (process->cycle + 1 < 10)
	{
		process->inst = 13;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + params[0]);
	if (params[1] && params[1] >= 1 && params[1] <= 16)
		process->registre[params[1] - 1] = params[0];
	if (!params[0])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_lldi(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("LLDI --> ");
	if (process->cycle + 1 < 50)
	{
		process->inst = 14;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 1);
	if (str[0] && str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + params[0]);
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] =
		recup_nb_32(vm->arena, process->position + params[0] + params[1]);
	if (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	process->position += 2 + params[3];
	printf(" Done\n");
	return (1);
}

int instruction_lfork(t_vm *vm, t_process *process, t_process **begin)
{
	printf("FORK --> ");
	if (process->cycle + 1 < 1000)
	{
		process->inst = 15;
		process->cycle++;
		printf("Progress\n");
		return (1);
	}
	if (!(create_new_process(begin, process, process->position + (recup_nb_16(vm->arena, process->position + 1)), process->numero_who_create_process)))
		return (0);
	process->cycle = 0;
	process->inst = 0;
	process->position += 3;
	printf(" Done\n");
	return (1);

