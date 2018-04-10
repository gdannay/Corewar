/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mng_buff.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 21:34:55 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 16:48:10 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		fill_count_buff(t_printf *ptf, char *concat, int add)
{
	if (ptf->cursor + add >= BUFFER)
	{
		ft_putstr(ptf->buff);
		ft_putstr(concat);
		ptf->surplus += add;
		ptf->surplus += ft_strlen(ptf->buff);
		if (ptf->cursor > 0)
			ft_bzero(ptf->buff, BUFFER + 1);
		ptf->cursor = 0;
		return (0);
	}
	(void)ft_strcat(ptf->buff, concat);
	ptf->cursor += add;
	return (1);
}

int		c_bu(t_printf *ptf, char *str)
{
	int	len_buff;
	int	len_str;

	len_buff = ptf->cursor;
	len_str = (int)ft_strlen(str);
	ptf->cursor += len_str;
	if (len_buff + len_str < BUFFER)
		return (1);
	ft_putstr(ptf->buff);
	ft_putstr(str);
	ptf->surplus += len_str;
	ptf->surplus += ptf->cursor;
	if (ptf->cursor > 0)
		ft_bzero(ptf->buff, BUFFER + 1);
	ptf->cursor = 0;
	return (0);
}
