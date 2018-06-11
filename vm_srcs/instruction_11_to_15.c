/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_11_to_15.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <vferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:40:09 by vferreir          #+#    #+#             */
/*   Updated: 2018/06/08 17:55:12 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	instruction_sti(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	if (process->cycle < 25)
		return (inst_progress(process, 11));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	params[0] = 1;
	take_params(vm->arena, process->position + 2, params, str);
	if (str[1] && str[1] == 'r' && params[1] >= 1 && params[1] <= 16)
		params[1] = process->registre[params[1] - 1];
	if (str[2] && str[2] == 'r' && params[2] >= 1 && params[2] <= 16)
		params[2] = process->registre[params[2] - 1];
	if (str[1] && str[1] == 'i')
		params[1] = recup_nb_32(vm->arena, process->position
				+ params[1]);
	if (params[0] && params[0] >= 1 && params[0] <= 16)
		write_in_arena_32(vm, process->registre[params[0] - 1],
				process->position
				+ ((params[1]) + (params[2])), process->color);
	return (inst_done(process, 2 + params[3]));
}

int	instruction_fork(t_vm *vm, t_process *process, t_process **begin)
{
	if (process->cycle < 800)
		return (inst_progress(process, 12));
	if (!(create_new_process(begin, process, process->position
						+ ((short int)recup_nb_16(vm->arena,
								process->position + 1) % IDX_MOD)
						, process->color)))
		return (0);
	vm->process++;
	return (inst_done(process, 3));
}

int	instruction_lld(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	if (process->cycle < 10)
		return (inst_progress(process, 13));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	params[0] = 0;
	take_params(vm->arena, process->position + 2, params, str);
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + params[0]);
	if (params[1] && params[1] >= 1 && params[1] <= 16)
		process->registre[params[1] - 1] = params[0];
	process->carry = (!params[0]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int	instruction_lldi(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	if (process->cycle < 50)
		return (inst_progress(process, 14));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	params[0] = 1;
	take_params(vm->arena, process->position + 2, params, str);
	if (str[0] && str[0] == 'r' && params[0] >= 1 && params[0] <= 16)
		params[0] = process->registre[params[0] - 1];
	if (str[1] && str[1] == 'r' && params[1] >= 1 && params[1] <= 16)
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

int	instruction_lfork(t_vm *vm, t_process *process, t_process **begin)
{
	if (process->cycle < 1000)
		return (inst_progress(process, 15));
	if (!(create_new_process(begin, process, process->position
					+ ((short int)recup_nb_16(vm->arena,
							process->position + 1)),
					process->color)))
		return (0);
	return (inst_done(process, 3));
}
