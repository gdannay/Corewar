/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:50:30 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/17 16:06:03 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

extern struct s_op op_tab[17];

int					compute_size_program(t_inst *first, int size)
{
	t_inst			*tmp;
	unsigned char	code;

	tmp = first;
	while (tmp)
	{
		code = tmp->codage;
		if (tmp->code != 0 && tmp->code != 11
				&& tmp->code != 8 && tmp->code != 14)
			size++;
		while (code)
		{
			if (code >> 6 == REG_CODE)
				size++;
			else if (code >> 6 == DIR_CODE && !op_tab[tmp->code].unknown)
				size += 4;
			else
				size += 2;
			code = code << 2;
		}
		size++;
		tmp = tmp->next;
	}
	return (size);
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

static header_t		*check_and_copy(char *line, header_t *header,
		int i, int type)
{
	int		j;
	int		k;
	int		l;

	j = find_next_char(line, 0);
	j += type == T_COMMAND_NAME ? ft_strlen(NAME_CMD_STRING)
		: ft_strlen(COMMENT_CMD_STRING);
	j = find_next_char(line, j);
	if (line[j] != '"')
		return (exit_error(i, j, header, line));
	k = ft_stridx(line + j + 1, "\"") + j + 1;
	if (!line[k])
		return (exit_error(i, j, header, line));
	if ((check_length(line, header, type, k - j)) == 0)
		return (NULL);
	l = k + 1;
	while (line[l] && (line[l] == ' ' || line[l] == '\t'))
		l++;
	if (line[l] && line[l] != COMMENT_CHAR)
		return (exit_error(i, l, header, line));
	if (type == T_COMMAND_NAME)
		ft_strncpy(header->prog_name, line + j + 1, k - j - 1);
	else if (type == T_COMMAND_COMMENT)
		ft_strncpy(header->comment, line + j + 1, k - j - 1);
	return (header);
}

static header_t		*get_infos(int fd, header_t *header, int *r)
{
	char	*line;
	int		ret;
	int		type;
	int		check;

	line = NULL;
	ret = 0;
	check = 0;
	while (check < 3 && (ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_strlen(line) > 0 && line[find_next_char(line, 0)] &&
				(type = get_type(line + find_next_char(line, 0))) != T_COMMENT)
		{
			if ((type != T_COMMAND_NAME && type != T_COMMAND_COMMENT) ||
					(check == 1 && type == T_COMMAND_NAME) ||
					(check == 2 && type == T_COMMAND_COMMENT))
				return (exit_error(*r, find_next_char(line, 0), header, line));
			if ((header = check_and_copy(line, header, *r, type)) == NULL)
				return (NULL);
			check += type == T_COMMAND_NAME ? 1 : 2;
		}
		*r = *r + 1;
		ft_strdel(&line);
	}
	return (ret == -1 ? exit_free(line, NULL, header) : header);
}

header_t			*create_header(int fd, int *row)
{
	header_t	*header;

	if ((header = (header_t *)ft_memalloc(sizeof(header_t))) == NULL)
		return (NULL);
	if ((header = get_infos(fd, header, row)) == NULL)
		return (NULL);
	return (header);
}
