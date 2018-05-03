/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:07:45 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 15:12:55 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		error_message(int line, int col, int type, char *str)
{
	if (type == T_INSTR)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] INTRUCTION \"%s\"\n",
				line, col, str);
	else if (type == T_STRING)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] STRING \"\"%s\"\"\n",
				line, col, str);
	else if (type == T_REG)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] REGISTER \"%s\"\n",
				line, col, str);
	else if (type == T_IND_LAB)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] INDIRECT_LABEL \"%s\"\n",
				line, col, str);
	else if (type == T_DIR_LAB)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] DIRECT_LABEL \"%s\"\n",
				line, col, str);
	else if (type == T_COMMAND_NAME)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] COMMAND_NAME \"%s\"\n",
				line, col, str);
	else if (type == T_COMMAND_COMMENT)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] COMMAND_COMMENT \"%s\"\n",
				line, col, str);
	else if (type == T_LAB)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s\"\n", line, col, str);
				else if (type == T_COMMENT)
					ft_dprintf(2,
							"Syntax error at token [TOKEN][%03d:%03d] COMMENT \"%s\"\n", line, col, str);
	else if (type == T_END)
		ft_dprintf(2,
				"Syntax error at token [TOKEN][%03d:%03d] ENDLINE\n", line, col);
	else if (type == ERROR)
		ft_dprintf(2, "Lexical Error at [%d:%d]\n", line, col);
	ft_strdel(&str);
}
