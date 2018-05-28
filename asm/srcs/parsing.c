/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:23:44 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/21 18:58:28 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

extern struct s_op op_tab[17];

int			find_next_char(char *str, int i)
{
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int			find_next_space(char *str, int i)
{
	int temp;

	temp = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i);
}

static void	delete_comment(char *str)
{
	int	i;
	int	com;

	i = 0;
	com = 0;
	while (str[i] && str[i] != COMMENT_CHAR)
		i++;
	ft_bzero(str + i, ft_strlen(str) - i);
}

static int	parse_line(char *line, char **label, int *row, t_inst **first)
{
	int			next;
	int 		ret;

	next = find_next_char(line, 0);
	ret = TRUE;
	if (line[next])
	{
		if (ft_strstr(line, ":") &&
				!line[find_next_char(line, ft_stridx(line, ":") + 1)] &&
				(ret = verif_label(line, *row)) == TRUE)
		{
			ft_strdel(label);
			if ((*label = ft_strsub(line, next, find_next_space(line, next) -
							next - 1)) == NULL)
				return (ERROR);
		}
		else if (ret == ERROR
			|| check_and_save(line, first, *row, label) == ERROR)
			return (ERROR);
	}
	return (TRUE);
}

t_inst		*parse_file(int fd, header_t *header, int *row)
{
	char		*line;
	char		*label;
	t_inst		*first;
	int			ret;

	line = NULL;
	first = NULL;
	label = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		delete_comment(line);
		if (!parse_line(line, &label, row, &first))
			return (exit_free(line, first, header));
		ft_strdel(&line);
		*row = *row + 1;
	}
	if (label)
		ft_strdel(&label);
	if (ret == -1)
		return (exit_free(line, first, header));
	return (first);
}
