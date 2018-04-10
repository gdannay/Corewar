/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 21:13:41 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/18 18:10:30 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_mod(va_list ap, t_parse *tmp, t_printf *ptf)
{
	char	c;

	(void)ap;
	if (tmp->moins > 0)
	{
		fill_count_buff(ptf, "%", 1);
		if (tmp->size_field > 0)
			fill_count_buff(ptf,
					ft_len_dup(tmp->size_field, ' '), tmp->size_field - 1);
	}
	else
	{
		c = (tmp->zero > 0) ? '0' : ' ';
		if (tmp->size_field > 0)
			fill_count_buff(ptf,
					ft_len_dup(tmp->size_field, c), tmp->size_field - 1);
		fill_count_buff(ptf, "%", 1);
	}
	return (1);
}
