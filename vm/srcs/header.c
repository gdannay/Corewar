/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:18:11 by gdannay           #+#    #+#             */
/*   Updated: 2018/06/06 15:59:57 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_player	*create_player(t_player **first, header_t *header, int pl_nbr)
{
	static	int	color = 1;
	static	int	i = -1;
	t_player	*new;
	t_player	*tmp;

	if ((new = (t_player *)ft_memalloc(sizeof(t_player))) == NULL)
		return (NULL);
	new->next = NULL;
	new->code = NULL;
	if (pl_nbr != -1)
		new->numero = pl_nbr * -1;
	else
	{
		new->numero = i;
		i--;
	}
	new->color = color;
	new->header = NULL;
	new->global_live = 0;
	new->last_live = 0;
	if (*first == NULL)
		*first = new;
	else
	{
		tmp = *first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	new->header = header;
	color++;
	return (new);
}

static header_t	*check_magic_length(header_t *header, char *name)
{
	int			*magic;

	magic = (int *)header;
	if ((*magic = (int)swap_32_bytes(*magic)) != COREWAR_EXEC_MAGIC)
	{
		return (header_error(header,
					"Error: File %s has an invalid header\n", name));
	}
	if ((int)swap_32_bytes(header->prog_size) > CHAMP_MAX_SIZE)
	{
		dprintf(2, "Error: File %s has too large a code (%d bytes > %d bytes)\n"
				, name, swap_32_bytes(header->prog_size), CHAMP_MAX_SIZE);
		free(header);
		return (NULL);
	}
	return (header);
}

static t_player	*read_header(t_player **first, int fd, char *name, int pl_nbr)
{
	int			ret;
	header_t	*header;
	t_player	*player;

	if (!first || (header = (header_t *)ft_memalloc(sizeof(header_t))) == NULL)
		return (NULL);
	if ((ret = read(fd, header, sizeof(header_t))) == -1)
		return (header_error(header,
					"A error occured while reading the file %s\n", name));
	else if (ret < (int)sizeof(header_t))
	{
		return (header_error(header,
					"Error: File %s is too small to be a champion\n", name));
	}
	if ((header = check_magic_length(header, name)) == NULL)
		return (NULL);
	if ((player = create_player(first, header, pl_nbr)) == NULL)
		return (header_error(header, "Error: Malloc failed in file %s", name));
	return (player);
}

int				read_file(t_player **first, int fd, char *name, int pl_nbr)
{
	char		*buff;
	char		test;
	int			ret;
	t_player	*player;

	if ((player = read_header(first, fd, name, pl_nbr)) == NULL)
		return (0);
	if ((buff = (char *)ft_memalloc(sizeof(char) *
					(int)swap_32_bytes(player->header->prog_size))) == NULL)
		return (0);
	ret = read(fd, buff, (int)swap_32_bytes(player->header->prog_size));
	if (ret == -1)
		return (code_error(buff, &player,
					"A error occured while reading the file %s\n", name));
	else if ((ret < (int)swap_32_bytes(player->header->prog_size))
			|| ((ret = read(fd, &test, 1)) != 0))
	{
		return (code_error(buff, &player,
					"Error: File %s has a code size that differs from what its header says\n",
					name));
	}
	player->code = buff;
	return (1);
}

t_player		*read_av(char **av, int ac, int i)
{
	t_player	*first;
	int			fd;
	int			pl_nbr;

	first = NULL;
	while (++i < ac)
	{
		pl_nbr = -1;
		if (!ft_strcmp(av[i], "-n"))
		{
			if (!av[i + 1] || (av[i + 1] && ft_atoi(av[i + 1]) <= 0))
			{
				ft_dprintf(2, "Invalid player number\n");
				return (NULL);
			}
			pl_nbr = ft_atoi(av[i + 1]);
			i += 2;
		}
		if ((fd = open(av[i], O_RDONLY)) == -1)
		{
			dprintf(2, "Can't read source file %s\n", av[i]);
			return (NULL);
		}
		else if ((read_file(&first, fd, av[i], pl_nbr)) == 0)
			return (NULL);
		close(fd);
	}
	return (first);
}
