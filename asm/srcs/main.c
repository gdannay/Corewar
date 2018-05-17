/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:44:45 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/17 12:35:44 by gdannay          ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_inst		*first;
	int			fd;
	header_t	*header;
	int			row;

	header = NULL;
	first = NULL;
	fd = -1;
	row = 1;
	//verifier si .s
	if (ac != 2)
	{
		write(2, "asm takes only one file as parameter\n", 37);
		return (-1);
	}
	if (av[1] && (fd = open(av[1], O_RDONLY)) == -1)
		return (-1);
	if ((header = create_header(fd, &row)) == NULL
		|| (first = parse_file(fd, header, &row)) == NULL)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (take_label(first) == ERROR)
	{
		exit_free(NULL, first, header);
		return (-1);
	}
	if ((write_in_cor(av[1], header, first)) == ERROR)
	{
		exit_free(NULL, first, header);
		return (-1);
	}
	exit_free(NULL, first, header);
	return (0);
}
