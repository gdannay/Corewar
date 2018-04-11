/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:23:44 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/11 16:52:09 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

static int	check_and_save(char *line, t_inst **first, t_inst *tmp)
{
	char	**elm;
	t_inst	*new;

	(void)first;
	(void)tmp;
	return (0);
	if ((elm = ft_splitspace(line)) == NULL)
		return (0);
	if ((new = (t_inst *)malloc(sizeof(t_inst))) == NULL)
		return (0);
}

t_inst		*parse_file(int fd)
{
	char		*line;
	t_inst		*first;
	t_inst		*tmp;
	int			ret;
	char		**split;

	line = NULL;
	first = NULL;
	tmp = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if ((split = ft_splitspace(line)) == NULL
			|| (check_and_save(line, &first, tmp) == 0))
			return (exit_free(line, first, NULL, split));
		ft_strdel(&line);
	}
	if (ret == -1)
		return (exit_free(line, first, NULL, split));
	return (first);
}
