/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:07:45 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/28 18:21:32 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			*exit_error(int row, int col, char **line, char **s)
{
	int		type;
	char	*msg;

	type = get_type(*s + col);
	msg = NULL;
	if (type & T_STRING)
		col++;
	if (type & ERROR)
		error_message(row, col + 1, type, NULL);
	else if (type & T_COMMENT)
	{
		if ((msg = ft_strdup(*s + col)) == NULL)
			return (NULL);
		error_message(row, col + 1, type, msg);
	}
	else
	{
		if ((msg = ft_strsub(*s, col, find_next_space(*s, col) - 1)) == NULL)
			return (NULL);
		error_message(row, col + 1, type, msg);
	}
	ft_strdel(s);
	ft_strdel(line);
	ft_strdel(&msg);
	return (NULL);
}

static void		next_messages(int line, int col, int type, char *str)
{
	if (type & T_COMMAND_NAME)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] COMMAND_NAME \"%s\"\n",
			line, col, str);
	else if (type & T_COMMAND_COMMENT)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] COMMAND_COMMENT \"%s\"\n",
			line, col, str);
	else if (type & T_LAB)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s\"\n",
			line, col, str);
	else if (type & T_COMMENT)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] COMMENT \"%s\"\n",
			line, col, str);
	else if (type & T_END)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] ENDLINE\n", line, col);
	else
		ft_dprintf(2, "Lexical Error at [%d:%d]\n", line, col);
}

int				error_message(int line, int col, int type, char *str)
{
	col++;
	if (type & T_INSTR)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] INTRUCTION \"%s\"\n",
			line, col, str);
	else if (type & T_STRING)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] STRING \"\"%s\"\"\n",
			line, col, str);
	else if (type & T_REG)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] REGISTER \"%s\"\n",
			line, col, str);
	else if (type & T_IND_LAB)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] INDIRECT_LABEL \"%s\"\n",
			line, col, str);
	else if (type & T_DIR_LAB)
		ft_dprintf(2,
			"Syntax error at token [TOKEN][%03d:%03d] DIRECT_LABEL \"%s\"\n",
			line, col, str);
	else
		next_messages(line, col, type, str);
	return (ERROR);
}

int				display_error(int infos, char *instr, char *param, char *line)
{
	int nb;
	int row;

	nb = infos >> 12 & 3;
	row = infos >> 15;
	if (infos & T_REG)
		ft_dprintf(2, "Invalid parameter %d type register for instruction %s\n",
				nb, instr);
	else if (infos & T_DIR)
		ft_dprintf(2, "Invalid parameter %d type direct for instruction %s\n",
				nb, instr);
	else if (infos & T_IND)
		ft_dprintf(2, "Invalid parameter %d type indirect for instruction %s\n",
				nb, instr);
	else
		error_message(row, ft_stridx(line, param), infos, param);
	return (ERROR);
}

void			*exit_free(char *line, t_inst *first, header_t *header)
{
	t_inst	*tmp;
	int		i;

	while (first)
	{
		tmp = first;
		first = first->next;
		if (tmp->label)
			ft_strdel(&(tmp->label));
		if (tmp->name)
			ft_strdel(&(tmp->name));
		i = -1;
		while (tmp->params[++i])
			ft_strdel(&(tmp->params[i]));
		free(tmp);
	}
	if (line)
		ft_strdel(&line);
	if (header)
		free(header);
	return (NULL);
}
