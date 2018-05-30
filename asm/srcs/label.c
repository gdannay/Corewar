/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 18:04:32 by vferreir          #+#    #+#             */
/*   Updated: 2018/05/30 16:47:19 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

extern struct s_op op_tab[17];

static int	add_label(t_inst *new, char *line, int i, int sauv)
{
	t_inst	*tmp;

	tmp = new->prev;
	if ((new->label = ft_strsub(line, sauv, i - sauv)) == NULL)
		return (-1);
	while (tmp)
	{
		if (tmp->label && ft_strcmp(tmp->label, new->label) == 0)
		{
			ft_dprintf(2, "Label \"%s\" is already used\n", new->label);
			return (-1);
		}
		tmp = tmp->prev;
	}
	return (find_next_char(line, i + 1));
}

int			save_label(char *line, int next, t_inst **first)
{
	t_inst	*new;
	t_inst	*tmp;

	if ((new = initialize_inst()) == NULL)
		return (ERROR);
	if (*first == NULL)
		*first = new;
	else
	{
		tmp = *first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	if ((new->label = ft_strsub(line, next,
			find_next_space(line, next) - next - 1)) == NULL)
		return (ERROR);
	return (TRUE);
}

int			fill_label(t_inst *new, char *line, int row)
{
	int		i;
	int		sauv;
	int		ret;

	ret = 1;
	i = find_next_char(line, 0);
	if (line[i] == ':')
	{
		ft_dprintf(2, "Label is empty [%03d:%03d]\n", row, i);
		return (-1);
	}
	sauv = i;
	while (line[i] && line[i] != ' ' && line[i] != '\t' &&
			line[i] != DIRECT_CHAR && line[i] != COMMENT_CHAR
			&& line[i] != SEPARATOR_CHAR)
	{
		if (line[i] == LABEL_CHAR && (ret = verif_label(line + sauv, row)))
			return (add_label(new, line, i, sauv));
		else if (line[i] == LABEL_CHAR && !ret)
			return (-1);
		i++;
	}
	return (sauv);
}

int			verif_label(char *line, int row)
{
	int i;

	i = find_next_char(line, 0) - 1;
	while (line[++i] && line[i] != LABEL_CHAR)
	{
		if (ft_strchr(LABEL_CHARS, line[i]) == NULL)
		{
			ft_dprintf(2,
		"Label \"%s\" does not respect LABEL_CHARS: \"%s\" [%03d:%03d]\n",
		line, LABEL_CHARS, row, i);
			return (ERROR);
		}
	}
	return (TRUE);
}
