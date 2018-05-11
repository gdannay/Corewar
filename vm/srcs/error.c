/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 15:44:27 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/10 15:06:26 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_players(t_player **first)
{
	t_player	*tmp;

	while (*first)
	{
		tmp = *first;
		*first = (*first)->next;
		if (tmp->header)
			free(tmp->header);
		ft_strdel(&(tmp->code));
		free(tmp);
	}
}

void	*header_error(header_t *header, char *str, char *name)
{
	ft_dprintf(2, str, name);
	free(header);
	return (NULL);
}

int	code_error(t_player **first, char *str, char *name)
{
	if (str && name)
		ft_dprintf(2, str, name);
	free_players(first);
	return (0);
}
