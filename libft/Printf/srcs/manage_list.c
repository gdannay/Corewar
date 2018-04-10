/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:48:01 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/12 19:07:30 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	del_list(t_parse **lst)
{
	if (!(*lst))
		return ;
	while (*lst)
	{
		ft_strdel(&(*lst)->begin);
		ft_strdel(&(*lst)->other);
		ft_strdel(&(*lst)->modif_len);
		free(*lst);
		(*lst) = (*lst)->next;
	}
	*lst = NULL;
}

/*
** void	print_list(t_parse *lst)
**{
**	t_parse	*tmp;
**
**	tmp = lst;
**	while (tmp)
**	{
**		dprintf(1, "plus = [%d], ", tmp->plus);
**		dprintf(1, "moins = [%d], ", tmp->moins);
**		dprintf(1, "space = [%d], ", tmp->space);
**		dprintf(1, "zero = [%d], ", tmp->zero);
**		dprintf(1, "precision = [%d], ", tmp->precision);
**		dprintf(1, "size_field = [%d], ", tmp->size_field);
**		dprintf(1, "diez = [%d], ", tmp->diez);
**		dprintf(1, "flag = [%c], ", tmp->flag);
**		dprintf(1, "begin = [%s], ", tmp->begin);
**		dprintf(1, "modif_len = [%s], ", tmp->modif_len);
**		dprintf(1, "other = [%s]\n", tmp->other);
**		tmp = tmp->next;
**	}
**	dprintf(1, "\n\n");
**}
*/
