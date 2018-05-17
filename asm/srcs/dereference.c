/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 15:11:01 by vferreir          #+#    #+#             */
/*   Updated: 2018/05/17 15:57:45 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern struct s_op op_tab[17];

static int	add_position(t_inst *list)
{
	int				pos;
	unsigned char	code;

	pos = 1;
	if (list->code != 0 && list->code != 11 &&
			list->code != 8 && list->code != 14)
		pos++;
	code = list->codage;
	while (code)
	{
		if (code >> 6 == REG_CODE)
			pos++;
		else if (code >> 6 == DIR_CODE && !op_tab[list->code].unknown)
			pos += 4;
		else
			pos += 2;
		code = code << 2;
	}
	return (pos);
}

static int	search_on_bottom(t_inst *list, char *str)
{
	int		pos;
	char	*label;

	pos = 0;
	label = ft_strstr(str, ":") + 1;
	while (list)
	{
		if (list->label && ft_strcmp(list->label, label) == 0)
			return (pos);
		pos += add_position(list);
		list = list->next;
	}
	return (-1);
}

static int	search_on_top(t_inst *list, char *str)
{
	int		pos;
	char	*label;

	pos = 0;
	label = ft_strstr(str, ":") + 1;
	while (list)
	{
		if (list->label && ft_strcmp(list->label, label) == 0)
			return (pos * -1);
		list = list->prev;
		if (list)
			pos += add_position(list);
	}
	return (-1);
}

static int	dereference(t_inst *inst, int i)
{
	int		pos;
	char	*conv;

	if ((pos = search_on_bottom(inst, inst->params[i])) == -1
			&& (pos = search_on_top(inst, inst->params[i])) == -1)
	{
		ft_printf("No such label %s\n", ft_strstr(inst->params[i], ":") + 1);
		return (ERROR);
	}
	if ((conv = ft_itoa(pos)) == NULL)
		return (ERROR);
	if (inst->params[i][0] == DIRECT_CHAR &&
			(inst->params[i] = ft_strjoin("%", conv)) == NULL)
	{
		ft_strdel(&conv);
		return (ERROR);
	}
	else if (inst->params[i][0] != DIRECT_CHAR
			&& (inst->params[i] = ft_strdup(conv)) == NULL)
	{
		ft_strdel(&conv);
		return (ERROR);
	}
	ft_strdel(&conv);
	return (TRUE);
}

int			take_label(t_inst *list)
{
	int		i;
	t_inst	*inst;
	char	*tmp;

	inst = list;
	while (inst)
	{
		i = -1;
		while (i < 3 && inst->params[++i])
		{
			if (inst->params[i][0] == LABEL_CHAR ||
					inst->params[i][1] == LABEL_CHAR)
			{
				tmp = inst->params[i];
				if (dereference(inst, i) == ERROR)
					return (ERROR);
				ft_strdel(&tmp);
			}
		}
		inst = inst->next;
	}
	return (TRUE);
}
