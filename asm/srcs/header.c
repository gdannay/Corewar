/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:50:30 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/11 19:38:48 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

static char	*cpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

static header_t	*get_infos(int fd, header_t *header)
{
	int		i;
	char	**split;
	char	*line;
	int		ret;

	i = -1;
	line = NULL;
	split = NULL;
	ret = 0;
	while (++i < 2 && (ret = get_next_line(fd, &line)) == 1)
	{
		if ((split = ft_splitspace(line)) == NULL)
			return (exit_free(line, NULL, header, split));
		if (ft_tablen(split) != 2 || (split[1] && get_type(split[1]) != T_STRING))
		{
			if (ft_tablen(split) == 1)
				error_message(i + 1, ft_strlen(line) + 1, T_END, NULL);
			else if (ft_tablen(split) > 2)
				error_message(i + 1, ft_stridx(line, split[2]) + 1, get_type(split[2]), split[2]);
			else if (ft_tablen(split) == 2)
				error_message(i + 1, ft_stridx(line, split[2]) + 1, get_type(split[1]), split[1]);
			return (exit_free(line, NULL, header, split));
		}
		if (ft_strcmp(split[0], NAME_CMD_STRING) == 0)
			cpy(header->prog_name, split[1]);
		else if (ft_strcmp(split[0], COMMENT_CMD_STRING) == 0)
			cpy(header->comment, split[1]);
		else
			return (exit_free(line, NULL, header, split));
		ft_tabdel(&split);
		ft_strdel(&line);
	}
	if (ret == -1)
		return (exit_free(line, NULL, header, split));
	return (header);
}

header_t	*create_header(fd)
{
	header_t	*header;

	if ((header = (header_t *)ft_memalloc(sizeof(header))) == NULL)
		return (NULL);
	if ((header = get_infos(fd, header)) == NULL
		|| (ft_strlen(header->comment) && 
			ft_strlen(header->prog_name)))
		return (header);
	return (exit_free(NULL, NULL, header, NULL));
}
