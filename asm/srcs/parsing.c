/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:23:44 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/03 16:41:14 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

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
	i = -1;
	while (++i < 4)
		new->params[i] = NULL;
	return (new);
}

static	t_inst	*check_and_save(char *line, t_inst **first, t_inst *tmp)
{
	t_inst	*new;
	int		idx;
	int		i;
	int		j;

	if ((new = initialize_inst()) == NULL)
		return (NULL);
	if (!(*first))
		*first = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
	if (((i = fill_label(new, line)) == -1) || (new->label && verif_label(new->label) == ERROR))
		return (NULL);
	if (ft_strlen(line + i) == 0)
		return (new);
	if ((idx = find_next_space(line, i)) == -1)
		return (NULL);
	if ((j = take_index_in_op(new, line + i, idx - i)) == -1)
		return (NULL);
	i = find_next_char(line, idx);
	if (check_params(new, line + i, j) == ERROR)
		return (NULL);
	return (new);
}

t_inst		*parse_file(int fd)
{
	char		*line;
	char		*temp;
	t_inst		*first;
	t_inst		*tmp;
	int			ret;

	line = NULL;
	first = NULL;
	tmp = NULL;
	temp = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (line[find_next_char(line, 0)] != COMMENT_CHAR && ft_strlen(line) - find_next_char(line, 0) > 0)
		{
			if (ft_strstr(line, ":") && ft_strlen(ft_strstr(line, ":") + 1) == 0 && verif_label(line) == TRUE)
			{
				while (ret == 1 && (!(ft_strlen(temp) - find_next_char(temp, 0)) || (temp[find_next_char(temp, 0)] == COMMENT_CHAR)))
				{
					if (temp)
						ft_strdel(&temp);
					ret = get_next_line(fd, &temp);
				}
				if (ret == -1 || !(line = ft_strjoindel(line, temp)))
				{
					ft_strdel(&temp);
					return (exit_free(line, first, NULL));
				}
				ft_strdel(&temp);
			}
			if (ft_strlen(line) > 0 && (tmp = check_and_save(line, &first, tmp)) == NULL)
				return (exit_free(line, first, NULL));
		}
		ft_strdel(&line);
	}
	if (ret == -1)
		return (exit_free(line, first, NULL));
	return (first);
}
