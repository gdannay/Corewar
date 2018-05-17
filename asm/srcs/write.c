/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 18:04:05 by vferreir          #+#    #+#             */
/*   Updated: 2018/05/17 16:06:08 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op op_tab[17];

static int write_header(header_t *header, t_inst *first, int fd)
{
	int	size;

	header->magic = swap_32_bytes(COREWAR_EXEC_MAGIC);
	size = compute_size_program(first, 0);
	header->prog_size = swap_32_bytes(size);
	if ((write(fd, header, sizeof(header_t))) < 0)
		return (ERROR);
	return (TRUE);
}

static int	write_registre(int fd, char *param)
{
	char	nb;
	
	nb = ft_atoi(param + 1);
	if ((write(fd, &nb, 1)) < 0)
		return (ERROR);
	return (TRUE);
}

static int	write_direct(t_inst *first, int fd, char *param)
{
	int nb;

	nb = ft_atoi(param + 1);
	if (op_tab[first->code].unknown == 1)
	{
		nb = swap_16_bytes(nb);
		if ((write(fd, &nb, 2)) < 0)
			return (ERROR);
	}
	else
	{
		nb = swap_32_bytes(nb);
		if ((write(fd, &nb, 4)) < 0)
			return (ERROR);
	}
	return (TRUE);
}

static int	write_indirect(int fd, char *param)
{
	int nb;

	nb = ft_atoi(param);
	nb = swap_16_bytes(nb);
	if ((write(fd, &nb, 2)) < 0)
		return (ERROR);
	return (TRUE);
}

static int	write_instruction(t_inst *first, int fd)
{
	int 	i;
	int		type;
	t_inst	*tmp;
	char	code;

	tmp = first;
	while (tmp)
	{
		i = -1;
		code = (char)(tmp->code + 1);
		if ((write(fd, &code, 1)) < 0)
			return (ERROR);
		if (tmp->code != 0 && tmp->code != 11
				&& tmp->code != 8 && tmp->code != 14
				&& (write(fd, &tmp->codage, 1)) < 0)
			return (ERROR);
		while (tmp->params[++i])
		{
			type = tmp->codage >> 6;
			tmp->codage = tmp->codage << 2;
			if (type == REG_CODE && !write_registre(fd, tmp->params[i]))
				return (ERROR);
			else if (type == DIR_CODE && !write_direct(tmp, fd, tmp->params[i]))
					return (ERROR);
			else if (type == IND_CODE && !write_indirect(fd, tmp->params[i]))
				return (ERROR);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

int		write_in_cor(char *av, header_t *header, t_inst *first)
{
	char *name;
	int fd;

	av = strrchr(av, '/') + 1;
	av[ft_strlen(av) - 2] = '\0';
	if ((name = ft_strjoin(av, ".cor")) == NULL)
		return (ERROR);
	if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) == -1
			|| (write_header(header, first, fd)) == ERROR
			|| (write_instruction(first, fd)) == ERROR)
		return (ERROR);
	ft_printf("Writing output program to %s\n", name);
	ft_strdel(&name);
	close(fd);
	return (TRUE);
}
