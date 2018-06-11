/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:47:21 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/08 14:02:23 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static	t_player	*fill_player(header_t *header,
		int pl_nbr, int i, int color)
{
	t_player	*new;

	if ((new = (t_player *)ft_memalloc(sizeof(t_player))) == NULL)
		return (NULL);
	new->next = NULL;
	new->code = NULL;
	if (pl_nbr != -1)
		new->numero = pl_nbr * -1;
	else
		new->numero = i;
	new->color = color;
	new->header = NULL;
	new->global_live = 0;
	new->last_live = 0;
	new->header = header;
	return (new);
}

t_player			*create_player(t_player **first,
		header_t *header, int pl_nbr)
{
	static	int	color = 1;
	static	int	i = -1;
	t_player	*new;
	t_player	*tmp;

	if (!(new = fill_player(header, pl_nbr, i, color)))
		return (NULL);
	if (*first == NULL)
		*first = new;
	else
	{
		tmp = *first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	color++;
	if (pl_nbr == -1)
		i--;
	return (new);
}
