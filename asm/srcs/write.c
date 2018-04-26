/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 18:04:05 by vferreir          #+#    #+#             */
/*   Updated: 2018/04/26 18:04:06 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void write_header(header_t *header, int fd)
{
  int nb;

  nb = swap_32_bytes(COREWAR_EXEC_MAGIC);
  write(fd, (char *)&nb, sizeof(int));
  write(fd, header->prog_name, PROG_NAME_LENGTH + 1);
  // Manque prog_size qui semble dependre de la taille total du programme
  write(fd, header->comment, COMMENT_LENGTH + 1);
}

void write_code_instruction(int fd, int code)
{
  (void)fd;
  (void)code;
}

void write_octet_codage(int fd, t_inst *list)
{
  (void)fd;
  (void)list;
}

void write_registre(int fd, char *param)
{
  (void)fd;
  (void)param;
}

void write_direct(int fd, char *param)
{
  (void)fd;
  (void)param;
}

void write_indirect(int fd, char *param)
{
  (void)fd;
  (void)param;
}


void write_instruction(t_inst *first, int fd)
{
  int i;
  (void)first;
  (void)fd;

  while (first)
  {
//    write_code_instruction(fd, first->code);
//    if (first->code != 1)
//      write_octet_codage(fd, first);
    i = -1;
    while (first->params[++i])
    {
      if (first->params[i][0] == 'r')
        write_registre(fd, first->params[i]);
      else if (first->params[i][0] == 'r')
        write_direct(fd, first->params[i]);
      else
        write_indirect(fd, first->params[i]);
    }
    first = first->next;
  }
}

void write_in_cor(header_t *header, t_inst *first)
{
  int fd;
	int nb;

  (void)first;
	fd = open("test_vince.cor", O_CREAT, S_IRWXU);
	fd = open("test_vince.cor", O_TRUNC);
	fd = open("test_vince.cor", O_RDWR);

  write_header(header, fd);
//  write_instruction(first, fd);

  (void)nb;
  /*
	nb = 1;
	write(fd, &nb, 1);
	nb = swap_32_bytes(12);
	write(fd, (char *)&nb, sizeof(int));

	nb = 11;
	write(fd, &nb, 1);
	nb = 104;
	write(fd, &nb, 1);
	nb = 1;
	write(fd, &nb, 1);
	nb = 0;
	write(fd, &nb, 1);
  */
}
