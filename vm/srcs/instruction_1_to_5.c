/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1_to_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:09:17 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/21 15:23:16 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int instruction_live(t_vm *vm, t_process *process, t_player *player)
{
	int numero_live;

	printf("LIVE --> ");
	if (process->cycle + 1 < 10)
		return (inst_progress(process, 1));
	numero_live = recup_nb_32(vm->arena, process->position + 1);
	while (player)
	{
		if (player->numero == numero_live)
			player->global_live++;
		player = player->next;
	}
	return (inst_done(process, 5));
}

int instruction_ld(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("LD --> ");
	if (process->cycle + 1 < 5)
		return (inst_progress(process, 2));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena,
			process->position + (params[0] % IDX_MOD));
	if (params[1] && params[1] >= 1 && params[1] <= 16)
		process->registre[params[1] - 1] = params[0];
	process->carry = (!params[0]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_st(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("ST --> ");
	if (process->cycle + 1 < 5)
		return (inst_progress(process, 3));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[1] && str[1] == 'r' && params[1] && params[1] >= 1 && params[1] <= 16
	&& params[0] && params[0] >= 1 && params[0] <= 16)
		process->registre[params[1] - 1] = process->registre[params[0] - 1];
	else if (params[0] && params[0] >= 1 && params[0] <= 16)
		write_in_arena_32(vm->arena, process->registre[params[0] - 1],
			process->position + (params[1] % IDX_MOD));
	process->carry = (!params[0]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_add(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("ADD --> ");
	if (process->cycle + 1 < 10)
		return (inst_progress(process, 4));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (params[0] && params[0] >= 1 && params[0] <= 16
		&& params[1] && params[1] >= 1 && params[1] <= 16
		&& params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = process->registre[params[0] - 1]
		+ process->registre[params[1] - 1];
	process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_sub(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("SUB --> ");
	if (process->cycle + 1 < 10)
		return (inst_progress(process, 5));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (params[0] && params[0] >= 1 && params[0] <= 16
		&& params[1] && params[1] >= 1 && params[1] <= 16
		&& params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = process->registre[params[0] - 1]
		- process->registre[params[1] - 1];
	process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_and(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("AND --> ");
	if (process->cycle + 1 < 6)
		return (inst_progress(process, 6));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'r' && params[0] && params[0] >= 1 && params[0] <= 16)
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r' && params[1] && params[1] >= 1 && params[1] <= 16)
		params[1] = process->registre[params[1] - 1];
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position
			+ (params[0] % IDX_MOD));
	if (str[1] && str[1] == 'i')
		params[1] = recup_nb_32(vm->arena, process->position
			+ (params[1] % IDX_MOD));
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = params[0] & params[1];
	process->carry = (!process->registre[params[2] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_or(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("OR --> ");
	if (process->cycle + 1 < 6)
		return (inst_progress(process, 7));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena,
			process->position + (params[0] % IDX_MOD));
	if (str[1] && str[1] == 'i')
		params[1] = recup_nb_32(vm->arena,
			process->position + (params[1] % IDX_MOD));
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = params[0] | params[1];
	process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_xor(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("XOR --> ");
	if (process->cycle + 1 < 6)
		return (inst_progress(process, 8));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = params[0] ^ params[1];
	process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_zjmp(t_vm *vm, t_process *process)
{
	printf("ZJMP --> ");
	if (process->cycle + 1 < 20)
		return (inst_progress(process, 9));
	return ((!process->carry) ? inst_done(process, 3)
	: inst_done(process, recup_nb_16(vm->arena, process->position + 1)));
}

int instruction_ldi(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("LDI --> ");
	if (process->cycle + 1 < 25)
		return (inst_progress(process, 10));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 1);
	if (str[0] && str[0] == 'r')
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena,
			process->position + (params[0] % IDX_MOD));
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] =
		recup_nb_32(vm->arena, process->position + params[0] + params[1]);
	process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_sti(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("STI --> ");
	if (process->cycle + 1 < 25)
		return (inst_progress(process, 11));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 1);
	if (str[1] && str[1] == 'r')
		params[1] = process->registre[params[1] - 1];
	if (str[2] && str[2] == 'r')
		params[2] = process->registre[params[2] - 1];
	if (str[1] && str[1] == 'i')
		params[1] = recup_nb_32(vm->arena, process->position
			+ (params[1] % IDX_MOD));
	if (params[0] && params[0] >= 1 && params[0] <= 16)
		write_in_arena_32(vm->arena, process->registre[params[0] - 1],
			process->position + ((params[1] % IDX_MOD) + (params[2] % IDX_MOD)));
	process->carry = (params[0] && params[0] >= 1 && params[0] <= 16
		&& !process->registre[params[0] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_fork(t_vm *vm, t_process *process, t_process **begin)
{
	printf("FORK --> ");
	if (process->cycle + 1 < 800)
		return (inst_progress(process, 12));
	if (!(create_new_process(begin, process, process->position
		+ (process->position + recup_nb_16(vm->arena, process->position + 1))
		% IDX_MOD - process->position, process->numero_who_create_process)))
		return (0);
	return (inst_done(process, 3));
}

int instruction_lld(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("LLD --> ");
	if (process->cycle + 1 < 10)
		return (inst_progress(process, 13));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + params[0]);
	if (params[1] && params[1] >= 1 && params[1] <= 16)
		process->registre[params[1] - 1] = params[0];
	process->carry = (!params[0]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_lldi(t_vm *vm, t_process *process)
{
	char str[4];
	int params[4];

	printf("LLDI --> ");
	if (process->cycle + 1 < 50)
		return (inst_progress(process, 14));
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
	process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
		&& !process->registre[params[2] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int instruction_lfork(t_vm *vm, t_process *process, t_process **begin)
{
	printf("LFORK --> ");
	if (process->cycle + 1 < 1000)
		return (inst_progress(process, 15));
	if (!(create_new_process(begin, process, process->position
		+ (recup_nb_16(vm->arena, process->position + 1)),
		process->numero_who_create_process)))
		return (0);
	return (inst_done(process, 3));
}
