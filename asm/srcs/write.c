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

extern t_op op_tab[17];

int calcul_size_program(t_inst *first)
{
  int i;
  int t;

  i = 0;
  while (first)
  {
    if (first->name)
    {
      i++;
      if (first->code != 1 && first->code != 12
        && first->code != 9 && first->code != 15)
        i++;
      t = -1;
      while (first->params[++t])
      {
        if (first->params[t][0] == 'r')
          i += 1;
        else if (first->params[t][0] == DIRECT_CHAR)
        {
          if (op_tab[first->code - 1].unknown == 1)
    				i += 2;
    			else
    				i += 4;
        }
        else
          i += 2;
      }
    }
    first = first->next;
  }
  return (i);
}

void write_header(header_t *header, t_inst *first, int fd)
{
  int nb;

  nb = swap_32_bytes(COREWAR_EXEC_MAGIC);

  write(fd, (char *)&nb, sizeof(int));
  write(fd, header->prog_name, PROG_NAME_LENGTH + 4);
  nb = calcul_size_program(first);
  nb = swap_32_bytes(nb);
  write(fd, (char *)&nb, sizeof(unsigned int));
  write(fd, header->comment, COMMENT_LENGTH + 4);
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

void write_direct(t_inst *first, int fd, char *param)
{
  int nb;

  nb = ft_atoi(param + 1);
  nb = swap_32_bytes(nb);

  if (op_tab[first->code - 1].unknown == 1)
  {
      nb = nb >> 16;
      write(fd, &nb, 2);
  }
  else
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
    printf("ICI = %s %d\n", first->name, first->code);
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
        write_direct(first, fd, first->params[i]);
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

  (void)header;
  // LIGNE A SUPPRIMER
    av = strrchr(av, '/') + 1;
  av[ft_strlen(av) - 2] = '\0';
  name = ft_strjoin(av, ".cor");
	if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH)) == -1)
    return ;
  write_header(header, first, fd);
  write_instruction(first, fd);
  close(fd);
}
