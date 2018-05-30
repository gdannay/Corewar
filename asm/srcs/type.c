/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matching.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:11:30 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/30 16:49:31 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			convert_type(char *str)
{
	int	type;

	type = get_type(str);
	if (type == T_DIR_LAB)
		return (T_DIR);
	else if (type == T_IND_LAB)
		return (T_IND);
	return (type);
}

static int	get_type_next_next(char *str)
{
	if (str[0] == LABEL_CHAR)
		return (T_IND_LAB);
	else if (str[0] == '"')
		return (T_STRING);
	else if (str[0] == COMMENT_CHAR || str[0] == ';')
		return (T_COMMENT);
	else if (!ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		return (T_COMMAND_NAME);
	else if (!ft_strncmp(str, COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
		return (T_COMMAND_COMMENT);
	else if (ft_strstr(str, ":") && ((!ft_strstr(str, ",")) ||
				(ft_strstr(str, ":") < ft_strstr(str, ","))))
		return (T_LAB);
	return (T_INSTR);
}

static int	get_type_next(char *str)
{
	int	i;

	i = 1;
	if (str[0] == DIRECT_CHAR && str[1] && str[1] == LABEL_CHAR)
	{
		i = 2;
		while (str[i] && ft_strchar(LABEL_CHARS, str[i]))
			i++;
		if (str[i] == '\0' || str[i] == '"' || str[i] == ' ' || str[i] == '\t')
			return (T_DIR_LAB);
		return (ERROR);
	}
	else if (str[0] == DIRECT_CHAR)
	{
		if (str[1] && str[2] && str[1] == '-' && ft_isdigit(str[2]))
			i++;
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (str[i - 1] != DIRECT_CHAR && (str[i] == '\0' ||
					str[i] == '"' || str[i] == ' ' || str[i] == '\t'))
			return (T_DIR);
		return (ERROR);
	}
	else
		return (get_type_next_next(str));
}

int			get_type(char *str)
{
	int i;

	i = 1;
	if (str == NULL || str[0] == '\0')
		return (T_END);
	if (str[0] == 'r' && str[1])
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (str[i] == '\0' || str[i] == '"' || str[i] == ' ' || str[i] == '\t')
			return (T_REG);
		return (T_INSTR);
	}
	else if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-')
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (str[i] == '\0' || str[i] == '"' || str[i] == ' ' || str[i] == '\t')
			return (T_IND);
		return (T_INSTR);
	}
	else
		return (get_type_next(str));
}
