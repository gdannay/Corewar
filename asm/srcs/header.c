/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:50:30 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 15:46:36 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

static int			exit_error(int line, int col, header_t *header, char *str)
{
	int type;

	type = get_type(str + col);
	if (type == T_STRING)
		col++;
	if (type == ERROR)
		error_message(line - 2, col + 1, type, NULL);
	else if (type == T_COMMENT)
		error_message(line - 2, col + 1, type, ft_strdup(str + col));
	else
		error_message(line, col + 1, type,
				ft_strsub(str, col, get_end_index(str + col)));
	free(header);
	ft_strdel(&str);
	return (0);
}

static int			check_length(char *line, header_t *header,
									int type, int length)
{
	if (length > ((type == T_COMMAND_NAME) ? PROG_NAME_LENGTH : COMMENT_LENGTH))
	{
		if (type == T_COMMAND_NAME)
			ft_dprintf(2, "Champion name too long (Max length %d)\n",
					PROG_NAME_LENGTH);
		else if (type == T_COMMAND_COMMENT)
			ft_dprintf(2, "Champion comment too long (Max length %d)\n",
					COMMENT_LENGTH);
		ft_strdel(&line);
		free(header);
		return (0);
	}
	return (1);
}

static int			check_and_copy(char *line, header_t *header,
									int i, int type)
{
	int		j;
	int		k;
	int		l;

	j = find_next_char(line, 0);
	j += type == T_COMMAND_NAME ? ft_strlen(NAME_CMD_STRING)
		: ft_strlen(COMMENT_CMD_STRING);
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] != '"')
		return (exit_error(i + 1, j, header, line));
	k = ft_stridx(line + j + 1, "\"") + j + 1;
	if (!line[k])
		return (exit_error(i + 3, j, header, line));
	if ((check_length(line, header, type, k - j)) == 0)
		return (0);
	l = k + 1;
	while (line[l] && (line[l] == ' ' || line[l] == '\t'))
		l++;
	if (line[l] && line[l] != COMMENT_CHAR)
		return (exit_error(i + 1, l, header, line));
	if (type == T_COMMAND_NAME)
		ft_strncpy(header->prog_name, line + j + 1, k - j - 1);
	else if (type == T_COMMAND_COMMENT)
		ft_strncpy(header->comment, line + j + 1, k - j - 1);
	return (1);
}

static header_t		*get_infos(int fd, header_t *header)
{
	int		i;
	char	*line;
	int		ret;
	int		type;

	i = 0;
	line = NULL;
	ret = 0;
	while ((!ft_strlen(header->prog_name) || !ft_strlen(header->comment)) && (ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_strlen(line) - find_next_char(line, 0) && (type = get_type(line + find_next_char(line, 0))) != T_COMMAND_NAME
				&& type != T_COMMAND_COMMENT && type != T_COMMENT)
		{
			exit_error(i + 1, 0, header, line);
			return (NULL);
		}
		if (ft_strlen(line) - find_next_char(line, 0) && type != T_COMMENT && ft_strlen(line) > 0 && check_and_copy(line, header, i, type) == 0)
			return (NULL);
		i++;
		ft_strdel(&line);
	}
	if (ret == -1)
		return (exit_free(line, NULL, header));
	return (header);
}

header_t			*create_header(int fd)
{
	header_t	*header;

	if ((header = (header_t *)ft_memalloc(sizeof(header_t))) == NULL)
		return (NULL);
	ft_bzero(header->prog_name, PROG_NAME_LENGTH + 1);
	if ((header = get_infos(fd, header)) == NULL
			|| (ft_strlen(header->comment) &&
				ft_strlen(header->prog_name)))
		return (header);
	free(header);
	return (NULL);
}
