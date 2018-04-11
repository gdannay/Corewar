/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:04:27 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/11 16:52:41 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_list(t_inst *first)
{
	t_inst	*tmp;

	while (first)
	{
		tmp = first;
		first = first->next;
		ft_strdel(&(tmp->label));
		ft_strdel(&(tmp->name));
		free(tmp);
	}
}

void	*exit_free(char *line, t_inst *first, header_t *header, char **split)
{
	free_list(first);
	if (line)
		ft_strdel(&line);
	if (header)
		free(header);
	if (split)
		ft_tabdel(&split);
	return (NULL);
}
