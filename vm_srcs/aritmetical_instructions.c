/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aritmetical_instructions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:57:50 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/18 14:00:20 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	instruction_add(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	ft_bzero(str, 4);
	ft_bzero(params, 4);
	if (process->cycle < 10)
		return (inst_progress(process, 4));
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str, 3);
	params[0] = 0;
	take_params(vm->arena, process->position + 2, params, str);
	if (check_op(3, str) == ERROR)
		return (inst_done(process, 2 + params[3]));
	if (params[0] && params[0] >= 1 && params[0] <= 16
			&& params[1] && params[1] >= 1 && params[1] <= 16
			&& params[2] && params[2] >= 1 && params[2] <= 16)
	{
		process->registre[params[2] - 1] = process->registre[params[0] - 1]
			+ process->registre[params[1] - 1];
		process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
				&& !process->registre[params[2] - 1]) ? 1 : 0;
	}
	return (inst_done(process, 2 + params[3]));
}

int	instruction_sub(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	ft_bzero(str, 4);
	ft_bzero(params, 4);
	if (process->cycle < 10)
		return (inst_progress(process, 5));
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str, 4);
	params[0] = 0;
	take_params(vm->arena, process->position + 2, params, str);
	if (check_op(4, str) == ERROR)
		return (inst_done(process, 2 + params[3]));
	if (params[0] && params[0] >= 1 && params[0] <= 16
			&& params[1] && params[1] >= 1 && params[1] <= 16
			&& params[2] && params[2] >= 1 && params[2] <= 16)
	{
		process->registre[params[2] - 1] = process->registre[params[0] - 1]
			- process->registre[params[1] - 1];
		process->carry = (params[2] && params[2] >= 1 && params[2] <= 16
				&& !process->registre[params[2] - 1]) ? 1 : 0;
	}
	return (inst_done(process, 2 + params[3]));
}
