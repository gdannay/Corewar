/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 15:44:27 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/11 18:44:41 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	*header_error(t_player **first, header_t *header,
	char *str, char *name)
{
	ft_dprintf(2, str, name);
	free(header);
	free_players(first);
	return (NULL);
}

int		code_error(char *buff, t_player **player, char *str, char *name)
{
	if (str && name)
		ft_dprintf(2, str, name);
	ft_strdel(&buff);
	free_players(player);
	return (0);
}

void	*error_read_av(t_player *first, char *format, char *param)
{
	if (param)
		ft_dprintf(2, format, param);
	else
		ft_dprintf(2, format);
	if (first)
		free_players(&first);
	return (NULL);
}
