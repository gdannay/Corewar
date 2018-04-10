/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:08:19 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 17:49:21 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	fill_diez_field(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	if (tmp->diez > 0)
	{
		if (tmp->flag == 'x' && ptf->nbl > 0)
			conv->diez = ft_strdup("0x");
		else if (tmp->flag == 'X' && ptf->nbl > 0)
			conv->diez = ft_strdup("0X");
		else if ((tmp->flag == 'o' || tmp->flag == 'O')
				&& (conv->arg[0] != '0' || ptf->nbl == 0))
			conv->diez = ft_strdup("0");
		else if (tmp->flag == 'b' && ptf->nbl > 0)
			conv->diez = ft_strdup("0b");
		if ((tmp->flag == 'x' || tmp->flag == 'X') && ptf->nbl > 0)
			fill_count_buff(ptf, conv->diez, ft_strlen(conv->diez));
		else if (tmp->flag != 'x' && tmp->flag != 'X')
			fill_count_buff(ptf, conv->diez, ft_strlen(conv->diez));
	}
	if (tmp->size_field > 0)
	{
		conv->field = ft_len_dup(tmp->size_field - ft_strlen(conv->arg)
				- ft_strlen(conv->diez) + 1, '0');
		fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
	}
}

void			conv_zero_unsigned(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	fill_diez_field(tmp, ptf, conv);
	if (ptf->nbl > 0)
		fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	else
	{
		if (((tmp->flag == 'o' || tmp->flag == 'O')
					&& !conv->diez && tmp->precision != 0)
				|| (tmp->flag != 'o' && tmp->flag != 'O'
					&& tmp->precision != 0))
			fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	}
}
