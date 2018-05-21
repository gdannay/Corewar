/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 15:44:27 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/21 18:31:35 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*header_error(header_t *header, char *str, char *name)
{
	ft_dprintf(2, str, name);
	free(header);
	return (NULL);
}

int	code_error(char *buff, t_player **player, char *str, char *name)
{
	if (str && name)
		ft_dprintf(2, str, name);
	ft_strdel(&buff);
	free_players(player);
	return (0);
}
