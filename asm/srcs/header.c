/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:50:30 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/21 18:46:26 by gdannay          ###   ########.fr       */
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

static void			save_infos(header_t *header, int type,
					char *str, int *check)
{
	if (type == T_COMMAND_NAME)
	{
		ft_strcpy(header->prog_name, str);
		*check = *check + 1;
	}
	else if (type == T_COMMAND_COMMENT)
	{
		ft_strcpy(header->comment, str);
		*check = *check + 2;
	}
}

static header_t		*get_infos(int fd, header_t *header, int *row)
{
	char		*line;
	char		*str;
	int			ret;
	int			type;
	int			check;

	check = 0;
	str = NULL;
	line = NULL;
	while (check < 3 && (ret = get_next_line(fd, &line)) == 1)
	{
		if (ft_strlen(line) > 0 && line[find_next_char(line, 0)] &&
				(type = get_type(line + find_next_char(line, 0))) != T_COMMENT)
		{
			if (check_type(header, check, type) == ERROR)
				return (exit_error(*row, find_next_char(line, 0), NULL, &line));
			if ((str = check_line(&line, fd, row, type)) == NULL)
				return (exit_free(NULL, NULL, header));
			save_infos(header, type, str, &check);
			ft_strdel(&str);
		}
		*row = *row + 1;
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
	//printf("IICICI = [%s] [%s]\n", header->prog_name, header->comment);
	return (header);
}
