/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:11:30 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 16:09:31 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	get_end_index(char *str)
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
	else if (str[ft_strlen(str) - 1] == LABEL_CHAR)
		return (T_IND_LAB);
	else if (str[0] == DIRECT_CHAR && str[1] && str[1] == LABEL_CHAR)
		return (T_DIR_LAB);
	else if (str[0] == DIRECT_CHAR)
		return (T_DIR);
	else if (str[0] == LABEL_CHAR)
		return (T_IND_LAB);
	else if (str[0] == '"')
		return (T_STRING);
	else if (str[0] == COMMENT_CHAR)
		return (T_COMMENT);
	else if ((ft_strstr(str, ":") && !ft_strstr(str, ",")) || (ft_strstr(str, ":") < ft_strstr(str, ",")))
		return (T_LAB);
	else if (!strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (T_COMMAND_NAME);
	else if (!strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		return (T_COMMAND_COMMENT);
	return (T_INSTR);
}
