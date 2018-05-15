#include "corewar.h"

int recup_nb_32(char *arena, int position)
{
  int nb;

  nb = (unsigned char)arena[(position + 3) % MEM_SIZE]
      | (unsigned char)arena[(position + 2) % MEM_SIZE] << 8
      | (unsigned char)arena[(position + 1) % MEM_SIZE] << 16
      | (unsigned char)arena[(position) % MEM_SIZE] << 24;
  return (nb);
}

int recup_nb_16(char *arena, int position)
{
  int nb;

  nb = (unsigned char)arena[(position + 1) % MEM_SIZE]
      | (unsigned char)arena[(position) % MEM_SIZE] << 8;
  return (nb);
}

void write_in_arena_32(char *arena, int registre, int pos)
{
  arena[pos % MEM_SIZE] = registre >> 24;
  arena[(pos + 1) % MEM_SIZE] = registre >> 16;
  arena[(pos + 2) % MEM_SIZE] = registre >> 8;
  arena[(pos + 3) % MEM_SIZE] = registre;
}

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

char *take_opcode(unsigned char c, char *str)
{
  int i;

  i = -1;
  while (++i < 4)
    str[i] = '\0';
  i = -1;
  while (++i < 3)
  {
    if (c >> 6 == 2)
      str[i] = 'd';
    else if (c >> 6 == 1)
      str[i] = 'r';
    else if (c >> 6 == 3)
      str[i] = 'i';
    else if (!c >> 6)
      return (NULL);
    c = c << 2;
  }
  return (str);
}

void take_params(char *arena, int pos, int *params, char *str, int unknown)
{
  int i;

  params[3] = 0;
  i = -1;
  while (str[++i])
  {
    if (str[i] == 'i' || (str[i] == 'd' && unknown != 0))
    {
      params[i] = recup_nb_16(arena, pos + params[3]);
      params[3] += 2;
    }
    else if (str[i] == 'd')
    {
      params[i] = recup_nb_32(arena, pos + params[3]);
      params[3] += 4;
    }
    else
    {
      params[i] = arena[(pos + params[3]) % MEM_SIZE];
      params[3] += 1;
    }
  }
}
