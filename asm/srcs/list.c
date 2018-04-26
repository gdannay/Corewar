/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:04:27 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 15:18:52 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_list(t_inst *first)
{
	t_inst	*tmp;
	int i;

	while (first)
	{
		tmp = first;
		first = first->next;
		ft_strdel(&(tmp->label));
		ft_strdel(&(tmp->name));
		i = -1;
		while (tmp->params[++i])
			ft_strdel(&(tmp->params[i]));
		free(tmp);
	}
}

void	*exit_free(char *line, t_inst *first, header_t *header)
{
	free_list(first);
	if (line)
		ft_strdel(&line);
	if (header)
		free(header);
	return (NULL);
}
