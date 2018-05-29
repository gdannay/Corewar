/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1_to_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:09:17 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/29 18:34:50 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern struct s_op op_tab[17];

int	instruction_live(t_vm *vm, t_process *process, t_player *player)
{
	int	numero_live;

	//printf("LIVE --> ");
	if (process->cycle < 10)
		return (inst_progress(process, 1));
	numero_live = recup_nb_32(vm->arena, process->position + 1);
	process->live++;
	while (player)
	{
		if (player->numero == numero_live)
			player->global_live++;
		player = player->next;
	}
	return (inst_done(process, 5));
}

int	instruction_ld(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	//printf("LD --> ");
	if (process->cycle < 5)
		return (inst_progress(process, 2));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[0] && str[0] == 'i')
		params[0] = recup_nb_32(vm->arena,
				process->position + params[0]) % IDX_MOD;
	if (params[1] && params[1] >= 1 && params[1] <= 16)
		process->registre[params[1] - 1] = params[0];
	process->carry = (!params[0]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int	instruction_st(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	//printf("ST --> ");
	if (process->cycle < 5)
		return (inst_progress(process, 3));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 0);
	if (str[1] && str[1] == 'r'
			&& params[1] && params[1] >= 1 && params[1] <= 16
			&& params[0] && params[0] >= 1 && params[0] <= 16)
		process->registre[params[1] - 1] = process->registre[params[0] - 1];
	else if (params[0] && params[0] >= 1 && params[0] <= 16)
		write_in_arena_32(vm, process->registre[params[0] - 1],
				process->position + (params[1] % IDX_MOD), process->numero_who_create_process);
	process->carry = (!params[0]) ? 1 : 0;
	return (inst_done(process, 2 + params[3]));
}

int	instruction_add(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	//printf("ADD --> ");
	if (process->cycle < 10)
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

int	instruction_sub(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	//printf("SUB --> ");
	if (process->cycle < 10)
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
