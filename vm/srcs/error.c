/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 15:44:27 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/04 17:30:32 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	free_players(t_player **first)
{
	t_player	*tmp;
	t_process	*tmp_p;

	while (*first)
	{
		tmp = *first;
		*first = (*first)->next;
		while (tmp->process)
		{
			tmp_p = tmp->process;
			tmp->process = tmp->process->next;
			free(tmp_p);
		}
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
