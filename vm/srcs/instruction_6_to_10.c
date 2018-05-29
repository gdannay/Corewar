/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_6_to_10.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <vferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:39:35 by vferreir          #+#    #+#             */
/*   Updated: 2018/05/29 13:22:02 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	instruction_and(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	//printf("AND --> ");
	if (process->cycle < 6)
		return (inst_progress(process, 6));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'r'
			&& params[0] && params[0] >= 1 && params[0] <= 16)
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r'
			&& params[1] && params[1] >= 1 && params[1] <= 16)
		params[1] = process->registre[params[1] - 1];
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position
				+ (params[0] % IDX_MOD));
	if (str[1] && str[1] == 'i')
		params[1] = recup_nb_32(vm->arena, process->position
				+ (params[1] % IDX_MOD));
	if (params[2] && params[2] >= 1 && params[2] <= 16)
		process->registre[params[2] - 1] = params[0] & params[1];
	process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
			&& !process->registre[params[2] - 1]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int	instruction_or(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	//printf("OR --> ");
	if (process->cycle < 6)
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

int	instruction_xor(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	//printf("XOR --> ");
	if (process->cycle < 6)
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

int	instruction_zjmp(t_vm *vm, t_process *process)
{
	//printf("ZJMP --> ");
	if (process->cycle < 20)
		return (inst_progress(process, 9));
	return ((!process->carry) ? inst_done(process, 3)
			: inst_done(process,
				recup_nb_16(vm->arena, process->position + 1)));
}

int	instruction_ldi(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	//printf("LDI --> ");
	if (process->cycle < 25)
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
