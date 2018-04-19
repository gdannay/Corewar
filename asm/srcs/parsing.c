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

int		find_next_char(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int		find_next_space(char *str, int i)
{
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

static	int		fill_label(t_inst *new, char *line)
{
	int		i;
	int		idx;

	i = find_next_char(line, 0);
	if ((idx = ft_stridx(line, ":")) != (int)ft_strlen(line) && idx > 0 && line[idx - 1] != '%')
	{
		new->label = ft_strsub(line, i, idx - i);
		i = find_next_char(line, idx + 1);
	}
	return (i);
}

static	t_inst	*check_and_save(char *line, t_inst **first, t_inst *tmp)
{
	t_inst	*new;
	int		idx;
	int		i;
	int		j;

	j = 0;
	if ((new = (t_inst *)malloc(sizeof(t_inst))) == NULL)
		return (0);
	new->label = NULL;
	new->name = NULL;
	new->next = NULL;
	if (!(*first))
		*first = new;
	else
	{
		tmp->next = new;
		new->prev = tmp;
	}
	i = fill_label(new, line);
	idx = find_next_space(line, i);
	while (ft_strncmp(line + i, op_tab[j].name, idx - i))
		j++;
	if (j > 15)
		return (NULL);
	new->name = ft_strdup(op_tab[j].name);
	i = find_next_char(line, idx);
	return (new);

}

t_inst		*parse_file(int fd)
{
	char		*line;
	t_inst		*first;
	t_inst		*tmp;
	int			ret;

	line = NULL;
	first = NULL;
	tmp = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_strlen(line) > 0 && (tmp = check_and_save(line, &first, tmp)) == NULL)
			return (exit_free(line, first, NULL));
		ft_strdel(&line);
	}
	if (ret == -1)
		return (exit_free(line, first, NULL));
	return (first);
}
