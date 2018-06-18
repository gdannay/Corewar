/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_opcode_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:15:03 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/18 14:20:57 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

extern struct s_op op_tab[17];

int			check_op(int process, char *str)
{
	int	i;
	int	type;

	i = -1;
	while (++i < op_tab[process].nb_par)
	{
		if (str[i] == 'd')
			type = T_DIR;
		else if (str[i] == 'i')
			type = T_IND;
		else if (str[i] == 'r')
			type = T_REG;
		if (!(type & op_tab[process].type_par[i]))
			return (ERROR);
	}
	return (TRUE);
}

int			take_opcode(unsigned char c, char *str, int process)
{
	int i;

	i = -1;
	while (++i < 4)
		str[i] = '\0';
	i = -1;
	while (++i < op_tab[process].nb_par)
	{
		if (c >> 6 == 2)
			str[i] = 'd';
		else if (c >> 6 == 1)
			str[i] = 'r';
		else if (c >> 6 == 3)
			str[i] = 'i';
		c = c << 2;
	}
	return (1);
}

static	int	octets_params(char *str, int unknown, int i)
{
	if (str[i] && (str[i] == 'i' || (str[i] == 'd' && unknown != 0)))
		return (2);
	else if (str[i] && str[i] == 'd')
		return (4);
	else if (str[i])
		return (1);
	return (0);
}

void		take_params(char *arena, int pos, int *params,
		char *str)
{
	int i;
	int	unknown;

	unknown = params[0];
	i = -1;
	while (++i < 4)
		params[i] = 0;
	i = -1;
	while (++i < 3)
	{
		if (str[i] && (str[i] == 'i' || (str[i] == 'd' && unknown != 0)))
			params[i] = (short int)recup_nb_16(arena, pos + params[3]);
		else if (str[i] && str[i] == 'd')
			params[i] = recup_nb_32(arena, pos + params[3]);
		else if (str[i])
			params[i] = arena[(pos + params[3]) % MEM_SIZE];
		params[3] += octets_params(str, unknown, i);
	}
}
