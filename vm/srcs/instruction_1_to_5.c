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
		return (0);
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
	return (5);
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
		return (0);
	}
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str);
	take_params(vm->arena, process->position + 2, params, str, 0);
	process->registre[params[1] - 1] = params[0];
	if (!params[0])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	printf(" Done\n");
	return (2 + params[3]);
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
		return (0);
	}
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str);
	take_params(vm->arena, process->position + 2, params, str, 0);
	write_in_arena_32(vm->arena, process->registre[params[0] - 1], process->position + (params[1] % IDX_MOD));
	process->cycle = 0;
	process->inst = 0;
	printf(" Done\n");
	return (2 + params[3]);
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
		return (0);
	}
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str);
	take_params(vm->arena, process->position + 2, params, str, 0);
	process->registre[params[2] - 1] = process->registre[params[0] - 1] + process->registre[params[1] - 1];
	if (!process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	printf(" Done\n");
	return (2 + params[3]);
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
		return (0);
	}
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str);
	take_params(vm->arena, process->position + 2, params, str, 0);
	process->registre[params[2] - 1] = process->registre[params[0] - 1] - process->registre[params[1] - 1];
	if (!process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	printf(" Done\n");
	return (2 + params[3]);
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
		return (0);
	}
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	process->registre[params[2] - 1] = params[0] & params[1];
	if (!process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	printf(" Done\n");
	return (2 + params[3]);
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
		return (0);
	}
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	process->registre[params[2] - 1] = params[0] | params[1];
	if (!process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	printf(" Done\n");
	return (2 + params[3]);
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
		return (0);
	}
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	process->registre[params[2] - 1] = params[0] ^ params[1];
	if (!process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	printf(" Done\n");
	return (2 + params[3]);
}

int instruction_zjmp(t_vm *vm, t_process *process)
{
	printf("ZJMP --> ");
	if (process->cycle + 1 < 20)
	{
		process->inst = 9;
		process->cycle++;
		printf("Progress\n");
		return (0);
	}
	process->cycle = 0;
	process->inst = 0;
	if (process->carry == 0)
		return (3);
	printf(" Done\n");
	printf("RECUP -> %d\n", recup_nb_16(vm->arena, process->position + 1));
	return (recup_nb_16(vm->arena, process->position + 1));
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
		return (0);
	}
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str);
	take_params(vm->arena, process->position + 2, params, str, 1);
	printf("%d, %d", params[0], params[1]);
	if (str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	process->registre[params[2] - 1] = recup_nb_32(vm->arena, process->position + params[0] + params[1]);
	printf("register = %d", process->registre[params[2] - 1]);
	if (!process->registre[params[2] - 1])
		process->carry = 1;
	else
		process->carry = 0;
	process->cycle = 0;
	process->inst = 0;
	printf(" Done\n");
	return (2 + params[3]);
}
