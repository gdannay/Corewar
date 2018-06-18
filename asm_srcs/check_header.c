/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 18:09:25 by gdannay           #+#    #+#             */
/*   Updated: 2018/06/11 18:40:31 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				check_length(char **str, char **line, int type, int length)
{
	if (length > ((type == T_COMMAND_NAME) ? PROG_NAME_LENGTH : COMMENT_LENGTH))
	{
		if (type == T_COMMAND_NAME)
			ft_dprintf(2, "Champion name too long (Max length %d)\n",
					PROG_NAME_LENGTH);
		else if (type == T_COMMAND_COMMENT)
			ft_dprintf(2, "Champion comment too long (Max length %d)\n",
					COMMENT_LENGTH);
		ft_strdel(line);
		ft_strdel(str);
		return (0);
	}
	return (1);
}

static int		add_line(char **str, char **read, int *i, int j)
{
	char	*tmp;

	tmp = *str;
	if ((*str = ft_strnjoin(*str, *read, j)) == NULL)
	{
		ft_strdel(&tmp);
		ft_strdel(read);
		return (ERROR);
	}
	ft_strdel(&tmp);
	if ((*read)[j])
	{
		j += find_next_char(ft_strstr(*read, "\"") + 1, 0) + 1;
		if ((*read)[j])
		{
			exit_error(*i, j, str, read);
			return (ERROR);
		}
		else
		{
			ft_strdel(read);
			return (TRUE);
		}
	}
	return (NEXT);
}

static int		multi_line_reader(char *line, char **str, int fd, int *i)
{
	int		ret;
	int		check;
	char	*read;

	if ((*str = ft_strjoin(line, "\n")) == NULL)
		return (ERROR);
	*i = *i + 1;
	while ((ret = get_next_line(fd, &read)) == 1)
	{
		if (read && !read[ft_stridx(read, "\"")] &&
				!(read = ft_strjoindel(read, "\n")))
			return (ERROR);
		if ((check = add_line(str, &read, i, ft_stridx(read, "\""))) == ERROR)
			return (ERROR);
		else if (check == TRUE)
			return (TRUE);
		*i = *i + 1;
		ft_strdel(&read);
	}
	ft_strdel(str);
	error_message(*i, 0, T_END, NULL);
	return (ERROR);
}

char			*check_line(char **line, int fd, int *i, int type)
{
	int		j;
	int		k;
	int		l;
	char	*str;

	j = find_next_char(*line, 0) + type == T_COMMAND_NAME ?
		ft_strlen(NAME_CMD_STRING) : ft_strlen(COMMENT_CMD_STRING);
	j = find_next_char(*line, j);
	if ((*line)[j] != '"')
		return (exit_error(*i, j, NULL, line));
	k = ft_stridx((*line) + j + 1, "\"") + j + 1;
	if (!(*line)[k] && multi_line_reader((*line) + j + 1, &str, fd, i) == ERROR)
		return (exit_free(*line, NULL, NULL));
	else if ((*line)[k])
	{
		l = k + 1;
		while ((*line)[l] && ((*line)[l] == ' ' || (*line)[l] == '\t'))
			l++;
		if ((*line)[l] && (*line)[l] != COMMENT_CHAR && (*line)[l] != ';')
			return (exit_error(*i, l, NULL, line));
		if ((str = ft_strndup((*line) + j + 1, k - j - 1)) == NULL)
			return (exit_free(*line, NULL, NULL));
	}
	return (!check_length(&str, line, type, ft_strlen(str)) ? NULL : str);
}

int				check_type(header_t *header, int check, int type)
{
	if ((type != T_COMMAND_NAME && type != T_COMMAND_COMMENT) ||
			(check == 1 && type == T_COMMAND_NAME) ||
			(check == 2 && type == T_COMMAND_COMMENT))
	{
		free(header);
		return (ERROR);
	}
	return (TRUE);
}
