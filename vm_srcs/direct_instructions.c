/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_instructions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:01:40 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/18 14:09:13 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	instruction_ld(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	ft_bzero(str, 4);
	ft_bzero(params, 4);
	if (process->cycle < 5)
		return (inst_progress(process, 2));
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str, 1);
	params[0] = 0;
	take_params(vm->arena, process->position + 2, params, str);
	if (check_op(1, str) == ERROR)
		return (inst_done(process, 2 + params[3]));
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena,
				process->position + (params[0] % IDX_MOD));
	if (params[1] && params[1] >= 1 && params[1] <= 16)
	{
		process->registre[params[1] - 1] = params[0];
		process->carry = (!params[0]) ? 1 : 0;
	}
	return (inst_done(process, 2 + params[3]));
}

int	instruction_st(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	ft_bzero(str, 4);
	ft_bzero(params, 4);
	if (process->cycle < 5)
		return (inst_progress(process, 3));
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str, 2);
	params[0] = 0;
	take_params(vm->arena, process->position + 2, params, str);
	if (check_op(2, str) == ERROR)
		return (inst_done(process, 2 + params[3]));
	if (str[1] && str[1] == 'r'
			&& params[1] && params[1] >= 1 && params[1] <= 16
			&& params[0] && params[0] >= 1 && params[0] <= 16)
		process->registre[params[1] - 1] = process->registre[params[0] - 1];
	else if (str[1] && str[1] != 'r'
	&& params[0] && params[0] >= 1 && params[0] <= 16)
		write_arena(vm, process->registre[params[0] - 1],
				process->position + (params[1] % IDX_MOD), process->color);
	return (inst_done(process, 2 + params[3]));
}

int	instruction_lld(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	ft_bzero(str, 4);
	ft_bzero(params, 4);
	if (process->cycle < 10)
		return (inst_progress(process, 13));
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str, 12);
	params[0] = 0;
	take_params(vm->arena, process->position + 2, params, str);
	if (check_op(12, str) == ERROR)
		return (inst_done(process, 2 + params[3]));
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena, process->position + params[0]);
	if (params[1] && params[1] >= 1 && params[1] <= 16)
	{
		process->registre[params[1] - 1] = params[0];
		process->carry = (!params[0]) ? 1 : 0;
	}
	return (inst_done(process, 2 + params[3]));
}
