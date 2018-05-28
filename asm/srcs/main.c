/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:44:45 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/28 13:42:56 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

uint16_t	swap_16_bytes(uint16_t nb)
{
	nb = (nb << 8) | (nb >> 8);
	return (nb);
}

static int	treat_file(int fd, char **av)
{
	header_t	*header;
	t_inst		*first;
	int			row;

	header = NULL;
	first = NULL;
	row = 1;
	if ((header = create_header(fd, &row)) == NULL
		|| (first = parse_file(fd, header, &row)) == NULL)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (take_label(first) == ERROR
		|| write_in_cor(av[1], header, first) == ERROR)
	{
		exit_free(NULL, first, header);
		return (-1);
	}
	exit_free(NULL, first, header);
	return (0);
}

int			main(int ac, char **av)
{
	int			fd;

	fd = -1;
	if (ac != 2)
	{
		write(2, "asm takes only one file as parameter\n", 37);
		return (-1);
	}
	if (!ft_strrchr(av[1], '.') || ft_strcmp(ft_strrchr(av[1], '.'), ".s") != 0)
	{
		ft_dprintf(2, "File \"%s\" is not a valid file\n", av[1]);
		return (-1);
	}
	if (av[1] && (fd = open(av[1], O_RDONLY)) == -1)
		return (-1);
	return (treat_file(fd, av));
}
