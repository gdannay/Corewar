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
  // MANQUE TAILLE DU CHAMPION
  write(fd, header->comment, COMMENT_LENGTH + 1);
}

void write_code_instruction(int fd, unsigned char code)
{
  write(fd, &code, 1);
}

void write_octet_codage(int fd, t_inst *list)
{
  unsigned char nb;
  int i;
  int diviseur;

  nb = 0;
  diviseur = 1;
  i = -1;
  while (list->params[++i])
  {
    if (list->params[i][0] == 'r')
      nb += 64 / diviseur;
    else if (list->params[i][0] == DIRECT_CHAR)
      nb += 128 / diviseur;
    else
      nb += 192 / diviseur;
    diviseur *= 4;
  }
  write(fd, &nb, 1);
}

void write_registre(int fd, char *param)
{
  unsigned char nb;

  nb = ft_atoi(param + 1);
  write (fd, &nb, 1);
}

void write_direct(int fd, char *param)
{
  int nb;


  // NORMALEMENT DIRECT EST EN 2 OCTET ET INDIRECT EN 4 MAIS L'ASM_42 FAIT DES TRUCS CHELOUS
  nb = ft_atoi(param + 1);
  nb = swap_32_bytes(nb);
  write(fd, &nb, 4);
}

void write_indirect(int fd, char *param)
{
  int nb;

  nb = ft_atoi(param);
  // PEUT ETRE CREER UNE FONCTION SWAP_16_bytes si >> 16 comporte des bugs
  nb = swap_32_bytes(nb);
  nb = nb >> 16;
  write(fd, &nb, 2);
}

void write_instruction(t_inst *first, int fd)
{
  int i;

  while (first)
  {
    write_code_instruction(fd, first->code);
    if (first->code != 1 && first->code != 12
      && first->code != 9 && first->code != 15)
      write_octet_codage(fd, first);
    i = -1;
    while (first->params[++i])
    {
      if (first->params[i][0] == 'r')
        write_registre(fd, first->params[i]);
      else if (first->params[i][0] == DIRECT_CHAR)
        write_direct(fd, first->params[i]);
      else
        write_indirect(fd, first->params[i]);
    }
    first = first->next;
  }
}

void write_in_cor(char *av, header_t *header, t_inst *first)
{
  char *name;
  int fd;

  // LIGNE A SUPPRIMER
    av = strrchr(av, '/') + 1;
  av[ft_strlen(av) - 2] = '\0';
  name = ft_strjoin(av, ".cor");
	fd = open(name, O_CREAT, S_IRWXU);
	fd = open(name, O_TRUNC);
	fd = open(name, O_RDWR);
  write_header(header, fd);
  write_instruction(first, fd);
}
