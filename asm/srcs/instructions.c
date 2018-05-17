/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 13:57:04 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/17 14:00:51 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op op_tab[17];

static t_inst		*initialize_inst(void)
{
	t_inst *new;
	int i;

	new = NULL;
	if ((new = (t_inst *)malloc(sizeof(t_inst))) == NULL)
		return (NULL);
	new->label = NULL;
	new->name = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->codage = 0;
	i = -1;
	while (++i < 4)
		new->params[i] = NULL;
	return (new);
}

static int take_index_in_op(t_inst *inst, char *line, int row, int *col)
{
	int j;
	int op_code;

	j = -1;
	op_code = -1;
	while (++j < 16)
	{
		if (!ft_strncmp(op_tab[j].name, line, ft_strlen(op_tab[j].name)))
			op_code = j;
	}
	if (op_code == -1)
	{
		ft_dprintf(2, "Instruction \"%s\" does not exist [TOKEN][%03d:%03d]\n", line, row, *col);
		return (ERROR);
	}
	inst->code = op_code;
	if ((inst->name = ft_strdup(op_tab[op_code].name)) == NULL)
		return (ERROR);
	*col = *col + ft_strlen(op_tab[op_code].name);
	return (TRUE);
}

int	check_and_save(char *line, t_inst **first, int row, char **label)
{
	t_inst	*new;
	t_inst	*tmp;
	int		i;

	if ((new = initialize_inst()) == NULL)
	{
		if (*label)
			ft_strdel(label);
		return (ERROR);
	}
	if (!(*first))
		*first = new;
	else
	{
		tmp = *first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	if (*label)
	{
		if ((new->label = ft_strdup(*label)) == NULL)
			return (ERROR);
		ft_strdel(label);
	}
	if ((i = fill_label(new, line, row)) == -1)
		return (ERROR);
	if ((take_index_in_op(new, line + i, row, &i)) == ERROR)
		return (ERROR);
	i = find_next_char(line, i);
	if (check_params(new, line, row, i) == ERROR)
		return (ERROR);
	return (TRUE);
}