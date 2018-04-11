/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:50:30 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/11 17:38:54 by gdannay          ###   ########.fr       */
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

header_t	*create_header(fd)
{
	header_t	*header;
	char		*line;
	int			ret;
	int			i;
	char		**split;

	if ((header = (header_t *)ft_memalloc(sizeof(header))) == NULL)
		return (NULL);
	i = -1;
	while (++i < 2 && (ret = get_next_line(fd, &line)) == 1)
	{
		if ((split = ft_splitspace(line)) == NULL)
			return (exit_free(line, NULL, header, split));
		if (ft_tablen(split) != 2)
			return (exit_free(line, NULL, header, split));
		if (ft_strcmp(split[0], NAME_CMD_STRING) == 0)
			cpy(header->prog_name, split[1]);
		else if (ft_strcmp(split[0], COMMENT_CMD_STRING) == 0)
			cpy(header->comment, split[1]);
		else
			return (exit_free(line, NULL, header, split));
		ft_strdel(&line);
	}
	if (ft_strlen(header->comment) && 
			ft_strlen(header->prog_name))
		return (header);
	return (exit_free(line, NULL, header, split));
}
