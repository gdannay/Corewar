/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_done_progress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:20:48 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/18 14:15:39 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		inst_progress(t_process *process, int inst)
{
	process->inst = inst;
	process->cycle++;
	return (1);
}

int		inst_done(t_process *process, int add_pos)
{
	process->cycle = 1;
	process->inst = 0;
	process->position += add_pos;
	process->position %= MEM_SIZE;
	if (process->position < 0)
		process->position += MEM_SIZE;
	process->position %= MEM_SIZE;
	return (1);
}
