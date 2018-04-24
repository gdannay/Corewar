/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:23:44 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 16:40:12 by gdannay          ###   ########.fr       */
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
	if (((i = fill_label(new, line)) == 0) || (new->label && verif_label(new->label) == ERROR))
		return (NULL);
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
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_strstr(line, ":") && ft_strlen(ft_strstr(line, ":") + 1) == 0 && verif_label(line) == TRUE)
		{
			if ((ret = get_next_line(fd, &temp)) != -1)
			{
				line = ft_strjoindel(line, temp);
				ft_strdel(&temp);
			}
		}
		if (ft_strlen(line) > 0 && (tmp = check_and_save(line, &first, tmp)) == NULL)
			return (exit_free(line, first, NULL));
		ft_strdel(&line);
	}
	if (ret == -1)
		return (exit_free(line, first, NULL));
	return (first);
}
