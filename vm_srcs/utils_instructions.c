/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:20:48 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/08 17:55:47 by clegirar         ###   ########.fr       */
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

int		take_opcode(unsigned char c, char *str)
{
	int i;

	i = -1;
	while (++i < 4)
		str[i] = '\0';
	i = -1;
	while (++i < 3)
	{
		if (c >> 6 == 2)
			str[i] = 'd';
		else if (c >> 6 == 1)
			str[i] = 'r';
		else if (c >> 6 == 3)
			str[i] = 'i';
		else if (!c >> 6)
			return (0);
		c = c << 2;
	}
	return (1);
}

void	take_params(char *arena, int pos, int *params,
		char *str)
{
	int i;
	int	unknown;

	unknown = params[0];
	params[3] = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == 'i' || (str[i] == 'd' && unknown != 0))
		{
			params[i] = (short int)recup_nb_16(arena, pos + params[3]);
			params[3] += 2;
		}
		else if (str[i] == 'd')
		{
			params[i] = recup_nb_32(arena, pos + params[3]);
			params[3] += 4;
		}
		else
		{
			params[i] = arena[(pos + params[3]) % MEM_SIZE];
			params[3] += 1;
		}
	}
}
