#include "corewar.h"

t_process	*create_process(t_process **process, t_process *tmp, int pos, int player_numero)
{
	t_process	*new;
	int i;

	if ((new = ft_memalloc(sizeof(t_process))) == NULL)
		return (NULL);
	new->numero_who_create_process = player_numero;
	new->position = pos;
	new->cycle = 0;
	new->live = 0;
	new->carry = 0;
	new->next = NULL;
	new->inst = 0;
	i = -1;
	while (++i < REG_NUMBER)
		new->registre[i] = 0;
  if (!(*process))
    *process = new;
  else
  {
    tmp->next = new;
    new->prev = tmp;
  }
	return (new);
}

t_process *initialize_process(t_player *player)
{
  t_process *process;
  t_process *tmp;
  int space;
  int i;

  process = NULL;
  tmp = NULL;
  space = MEM_SIZE / nbr_players(player);
  i = 0;
  while (player)
  {
    tmp = create_process(&process, tmp, space * i, player->numero);
		tmp->registre[0] = player->numero;
    player = player->next;
    i++;
  }
  return (process);
}
