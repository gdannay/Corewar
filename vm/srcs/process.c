#include "corewar.h"

int 	create_new_process(t_process **begin, t_process *process, int pos, int n)
{
	t_process	*new;
	int				i;

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		return (0);
	new->numero_who_create_process = n;
	new->position = pos;
	new->cycle = 0;
	new->live = process->live;
	new->carry = process->carry;
	new->inst = 0;
	i = -1;
	while (++i < REG_NUMBER)
		new->registre[i] = process->registre[i];
	new->next = *begin;
	(*begin)->prev = new;
	*begin = new;
	return (1);
}

t_process	*create_process(t_process **process, t_process *tmp, int pos, int player_numero)
{
	t_process	*new;
	int i;

	if ((new = (t_process *)ft_memalloc(sizeof(t_process))) == NULL)
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
	while (player->next)
		player = player->next;
  while (player)
  {
    if (!(tmp = create_process(&process, tmp, space * i, player->numero)))
			return (NULL);
		tmp->registre[0] = player->numero;
    player = player->prev;
    i++;
  }
  return (process);
}
