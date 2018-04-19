/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:23:44 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 14:03:54 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

int	get_index(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '"')
			return (i);
		i++;
	}
	return (i);
}

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

int			get_type(char *str)
{
	int i;

	i = 1;
	if (str == NULL || str[0] == '\0')
		return (T_END);
	if (str[0] == 'r' && str[1])
	{
		while (str[i] && str[i] != '"' && str[i] != ' ' && str[i] != '\t' && ft_isdigit(str[i]))
			i++;
		if (str[i] == '\0' || str[i] == '"' || str[i] == ' ' || str[i] == '\t')
			return (T_REG);
		return (T_INSTR);
	}
	else if (str[ft_strlen(str) - 1] == ':')
		return (T_IND_LAB);
	else if (str[0] == '%' && str[1] && str[1] == ':')
		return (T_DIR_LAB);
	else if (str[0] == '%')
		return (T_DIR);
	else if (str[0] == ':')
		return (T_IND_LAB);
	else if (str[0] == '"')
		return (T_STRING);
	else if (!strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (T_COMMAND_NAME);
	else if (!strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (T_COMMAND_COMMENT);
	return (T_INSTR);
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
	split = NULL;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if ((split = ft_splitspace(line)) == NULL
				|| (check_and_save(line, &first, tmp) == 0))
			return (exit_free(line, first, NULL, split));
		ft_strdel(&line);
		ft_tabdel(&split);
	}
	if (ret == -1)
		return (exit_free(line, first, NULL, split));
	return (first);
}
