/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_zero_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:10:27 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 17:49:16 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	fill_diez_preci(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	if (tmp->diez > 0)
	{
		if (tmp->flag == 'x')
			conv->diez = ft_strdup("0x");
		else if (tmp->flag == 'X')
			conv->diez = ft_strdup("0X");
		else if ((tmp->flag == 'o' || tmp->flag == 'O')
				&& (conv->arg[0] != '0' || ptf->nbl == 0))
			conv->diez = ft_strdup("0");
	}
	if (tmp->precision > 0)
	{
		if ((tmp->flag == 'o' || tmp->flag == 'O') && ptf->nbl > 0)
			conv->preci = ft_len_dup(tmp->precision - ft_strlen(conv->arg)
					- ft_strlen(conv->diez) + 1, '0');
		else
			conv->preci = ft_len_dup(tmp->precision
					- ft_strlen(conv->arg) + 1, '0');
	}
}

static	void	fill_field(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	if (tmp->size_field > 0)
	{
		if (ptf->nbl > 0)
			conv->field = ft_len_dup(tmp->size_field - ft_strlen(conv->arg)
					- ft_strlen(conv->diez) - ft_strlen(conv->preci) + 1, ' ');
		else
		{
			if (tmp->precision != 0)
				conv->field = ft_len_dup(tmp->size_field - ft_strlen(conv->arg)
						- ft_strlen(conv->preci) + 1, ' ');
			else
				conv->field = ft_len_dup(tmp->size_field - ft_strlen(conv->diez)
						+ 1, ' ');
		}
	}
}

static	void	fill_buff_moins(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	if (tmp->moins > 0)
	{
		if ((tmp->flag == 'x' || tmp->flag == 'X') && ptf->nbl > 0)
			fill_count_buff(ptf, conv->diez, ft_strlen(conv->diez));
		else if (tmp->flag != 'x' && tmp->flag != 'X')
			fill_count_buff(ptf, conv->diez, ft_strlen(conv->diez));
		fill_count_buff(ptf, conv->preci, ft_strlen(conv->preci));
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
		fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
	}
}

static	void	fill_buff_no_moins(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	if (tmp->moins < 0)
	{
		fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
		if ((tmp->flag == 'x' || tmp->flag == 'X') && ptf->nbl > 0)
			fill_count_buff(ptf, conv->diez, ft_strlen(conv->diez));
		else if (tmp->flag != 'x' && tmp->flag != 'X')
			fill_count_buff(ptf, conv->diez, ft_strlen(conv->diez));
		fill_count_buff(ptf, conv->preci, ft_strlen(conv->preci));
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
}

void			conv_no_zero_unsigned(t_parse *tmp,
		t_printf *ptf, t_conv *conv)
{
	fill_diez_preci(tmp, ptf, conv);
	fill_field(tmp, ptf, conv);
	fill_buff_moins(tmp, ptf, conv);
	fill_buff_no_moins(tmp, ptf, conv);
}
