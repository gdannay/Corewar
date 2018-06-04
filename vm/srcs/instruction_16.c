/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_16.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <vferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:40:19 by vferreir          #+#    #+#             */
/*   Updated: 2018/06/04 11:16:41 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	instruction_aff(t_vm *vm, t_process *process)
{
	char	str[4];
	int		params[4];

	printf("AFF --> ");
	if (process->cycle < 2)
		return (inst_progress(process, 16));
	if (!(take_opcode(vm->arena[(process->position + 1) % MEM_SIZE], str)))
		return (1);
	take_params(vm->arena, process->position + 2, params, str, 1);
	if (params[0] && params[0] >= 1 && params[0] <= 16)
		params[0] = process->registre[params[0] - 1];
	ft_printf("%c\n", params[0] % 256);
	return (inst_done(process, 2 + params[3]));
}
