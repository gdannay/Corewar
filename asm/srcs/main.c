/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:44:45 by clegirar          #+#    #+#             */
/*   Updated: 2018/04/19 15:18:29 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void lecture_list_temp(t_inst *first)
{
	while (first)
	{
		if (first->label)
			printf("%-8s", first->label);
		else
			printf("        ");
		if (first->name)
			printf("%-8s", first->name);
		if (first->params[0])
			printf("p1: %s", first->params[0]);
			if (first->params[1])
				printf(" | p2: %s", first->params[1]);
				if (first->params[2])
					printf(" | p3: %s", first->params[2]);
		printf("\n");
		first = first->next;
	}
}

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

void ecriture_test(header_t *header)
{
	int fd;
	char *test;
	int nb;

	fd = open("test_vince.cor", O_CREAT, S_IRWXU);
	fd = open("test_vince.cor", O_RDWR);
	nb = swap_32_bytes(COREWAR_EXEC_MAGIC);
	test = (char *)&nb;
	write(fd, test, 4);
	write(fd, header->prog_name, PROG_NAME_LENGTH + 1);
	write(fd, header->comment, COMMENT_LENGTH + 1);
	write(fd, "yolo\n", 5);
	char buf[2];
	fd = open("../champs/test_vince.cor", O_RDONLY);
	while (read(fd, buf, 1))
	{
//		if (buf[0] != '\0')
//			printf("%d\n", buf[0]);
	}
}

int	main(int ac, char **av)
{
	t_inst		*first;
	int			fd;
	header_t	*header;

	header = NULL;
	first = NULL;
	fd = -1;
	if (ac != 2)
	{
		write(2, "asm takes only one file as parameter\n", 37);
		return (-1);
	}
	if (av[1] && (fd = open(av[1], O_RDONLY)) == -1)
		return (-1);
	if ((header = create_header(fd)) == NULL
		|| (first = parse_file(fd)) == NULL)
	{
		close(fd);
		return (-1);
	}

	ecriture_test(header);

	exit_free(NULL, first, header);
	return (0);
}
