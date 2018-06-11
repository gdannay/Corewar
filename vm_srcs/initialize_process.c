/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <vferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:58:20 by vferreir          #+#    #+#             */
/*   Updated: 2018/06/08 15:22:41 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					create_new_process(t_process **begin,
		t_process *process, int pos, int n)
{
	t_process	*new;
	int			i;

	if (!(new = (t_process *)ft_memalloc(sizeof(t_process))))
		return (0);
	new->color = n;
	new->position = pos;
	new->cycle = 1;
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

static	t_process	*create_process(t_process **process,
		t_process *tmp, int pos, int color)
{
	t_process	*new;
	int			i;

	if ((new = (t_process *)ft_memalloc(sizeof(t_process))) == NULL)
		return (NULL);
	new->color = color;
	new->position = pos;
	new->cycle = 1;
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

t_process			*initialize_process(t_map *map)
{
	t_player	*tmp_p;
	t_process	*process;
	t_process	*tmp;
	int			i;

	process = NULL;
	tmp = NULL;
	i = 0;
	tmp_p = map->player;
	while (tmp_p)
	{
		if (!(tmp = create_process(&process,
						tmp, map->vm->ecart * i, tmp_p->color)))
			return (NULL);
		tmp->registre[0] = tmp_p->numero;
		tmp_p = tmp_p->next;
		i++;
	}
	return (process);
}
