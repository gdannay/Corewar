/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 18:18:58 by vferreir          #+#    #+#             */
/*   Updated: 2018/05/17 15:59:22 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern struct s_op op_tab[17];

int			convert_type(char *str)
{
	int	type;

	type = get_type(str);
	if (type == T_DIR_LAB)
		return (T_DIR);
	else if (type == T_IND_LAB)
		return (T_IND);
	return (type);
}

static int	get_codage(int type)
{
	if (type == T_REG)
		return (REG_CODE);
	else if (type == T_DIR)
		return (DIR_CODE);
	return (IND_CODE);
}

static int	check_errors(char *split, char *line, int row, int j)
{
	int		idx_next;
	char	next;

	idx_next = find_next_char(split, find_next_space(split, j));
	if ((next = split[idx_next]))
	{
		error_message(row, ft_stridx(line, split) + idx_next,
				get_type(split + idx_next), split + idx_next);
		return (ERROR);
	}
	return (TRUE);
}

static int	parse_params(t_inst *new, char **split, char *ln, int row)
{
	int		i;
	int		type;
	int		j;

	i = -1;
	while (split[++i])
	{
		j = find_next_char(split[i], 0);
		type = convert_type(split[i] + j);
		new->codage += get_codage(type);
		new->codage = new->codage << 2;
		if (!(type & op_tab[new->code].type_par[i]))
		{
			display_error(type | i << 12 | row << 15, new->name, split[i], ln);
			return (ERROR);
		}
		if (check_errors(split[i], ln, row, j) == ERROR)
			return (ERROR);
		if ((new->params[i] = ft_strsub(split[i], j,
						find_next_space(split[i], j) - j)) == NULL)
			return (ERROR);
	}
	while (++i < 4)
		new->codage = new->codage << 2;
	return (TRUE);
}

int			check_params(t_inst *new, char *line, int row, int col)
{
	char	**split;
	char	*params;

	params = line + col;
	if ((split = ft_strsplit(params, SEPARATOR_CHAR)) == NULL)
		return (ERROR);
	if (ft_tablen(split) != op_tab[new->code].nb_par)
	{
		ft_dprintf(2,
				"Invalid parameter count for instruction %s\n", new->name);
		ft_tabdel(&split);
		return (ERROR);
	}
	if (parse_params(new, split, line, row) == ERROR)
	{
		ft_tabdel(&split);
		return (ERROR);
	}
//	printf("ICI = %d [%s] [%s] [%s] [%s] [%s] [%x]\n", new->code, new->label, new->name, new->params[0], new->params[1], new->params[2], new->codage);
	ft_tabdel(&split);
	return (TRUE);
}
