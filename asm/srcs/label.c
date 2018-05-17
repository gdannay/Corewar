/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 18:04:32 by vferreir          #+#    #+#             */
/*   Updated: 2018/05/17 15:14:15 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

extern struct s_op op_tab[17];

static int	save_label(t_inst *new, char *line, int i, int sauv)
{
	if (new->label)
		ft_strdel(&(new->label));
	if ((new->label = ft_strsub(line, sauv, i - sauv)) == NULL)
		return (-1);
	return (find_next_char(line, i + 1));
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
	while (line[i] && line[i] != ' ' && line[i] != DIRECT_CHAR
			&& line[i] != COMMENT_CHAR && line[i] != SEPARATOR_CHAR)
	{
		if (line[i] == LABEL_CHAR && (ret = verif_label(line + sauv, row)))
			return (save_label(new, line, i, sauv));
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
			"Label \"%s\" does not respect LABEL_CHARS: \"%s\"\n [%03d:%03d]",
			line, LABEL_CHARS, row, i);
			return (ERROR);
		}
	}
	return (TRUE);
}