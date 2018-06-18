/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_rest_instructions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 13:54:19 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/18 14:04:41 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	instruction_live(t_vm *vm, t_process *process, t_player *player)
{
	int	numero_live;

	if (process->cycle < 10)
		return (inst_progress(process, 1));
	numero_live = recup_nb_32(vm->arena, process->position + 1);
	process->live += 1;
	vm->nbr_live += 1;
	while (player)
	{
		if (player->numero == numero_live)
		{
			player->last_live = vm->cycle;
			player->global_live++;
		}
		player = player->next;
	}
	return (inst_done(process, 5));
}

int	instruction_zjmp(t_vm *vm, t_process *process)
{
	if (process->cycle < 20)
		return (inst_progress(process, 9));
	return ((!process->carry) ? inst_done(process, 3)
			: inst_done(process,
				(short int)recup_nb_16(vm->arena, process->position + 1)
				% IDX_MOD));
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

int	instruction_aff(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	if (process->cycle < 2)
		return (inst_progress(process, 16));
	take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str, 15);
	params[0] = 1;
	take_params(vm->arena, process->position + 2, params, str);
	if (check_op(15, str) == ERROR)
		return (inst_done(process, 2 + params[3]));
	if (params[0] && params[0] >= 1 && params[0] <= 16)
		params[0] = process->registre[params[0] - 1];
	if (vm->flag & A_FLAG)
		ft_printf("%c\n", params[0] % 256);
	return (inst_done(process, 2 + params[3]));
}
