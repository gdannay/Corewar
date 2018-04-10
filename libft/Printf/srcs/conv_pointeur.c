/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_pointeur.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:05:30 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/22 17:39:05 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	conv_zero(va_list ap, t_parse *tmp,
		t_printf *ptf, t_conv *conv)
{
	conv->arg = ft_lltoa_base((unsigned long long)
			va_arg(ap, unsigned long long), 16, 'a');
	ptf->nbl = ft_atoll_base(conv->arg, 16, 'a');
	conv->prefix = ft_strdup("0x");
	if (tmp->size_field > 0)
		conv->field = ft_len_dup(tmp->size_field - ft_strlen(conv->prefix)
				- ft_strlen(conv->arg) + 1, '0');
	fill_count_buff(ptf, conv->prefix, 2);
	fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
	if (ptf->nbl > 0)
		fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	else
	{
		if (tmp->precision != 0)
			fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	}
}

static	void	aff_zero_moins(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	fill_count_buff(ptf, conv->prefix, 2);
	fill_count_buff(ptf, conv->preci, ft_strlen(conv->preci));
	if (ptf->nbl > 0)
		fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	else
	{
		if (tmp->precision != 0)
			fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	}
	fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
}

static	void	aff_zero(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
	fill_count_buff(ptf, conv->prefix, 2);
	fill_count_buff(ptf, conv->preci, ft_strlen(conv->preci));
	if (ptf->nbl > 0)
		fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	else
	{
		if (tmp->precision != 0)
			fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	}
}

static	void	conv_no_zero(va_list ap, t_parse *tmp,
		t_printf *ptf, t_conv *conv)
{
	conv->prefix = ft_strdup("0x");
	conv->arg = ft_lltoa_base((unsigned long long)
			va_arg(ap, void *), 16, 'a');
	ptf->nbl = ft_atoll_base(conv->arg, 16, 'a');
	if (tmp->precision > 0)
		conv->preci = ft_len_dup(tmp->precision
				- ft_strlen(conv->arg) + 1, '0');
	if (tmp->size_field > 0)
		conv->field = ft_len_dup(tmp->size_field - ft_strlen(conv->arg)
				- ft_strlen(conv->prefix) - ft_strlen(conv->field)
				- ft_strlen(conv->preci) + 1, ' ');
	if (tmp->moins > 0)
		aff_zero_moins(tmp, ptf, conv);
	else
		aff_zero(tmp, ptf, conv);
}

int				conv_pointeur(va_list ap, t_parse *tmp, t_printf *ptf)
{
	t_conv	conv;

	conv.prefix = NULL;
	conv.arg = NULL;
	conv.field = NULL;
	conv.preci = NULL;
	if (tmp->zero > 0)
	{
		if (tmp->moins > 0 || tmp->precision >= 0)
			conv_no_zero(ap, tmp, ptf, &conv);
		else
			conv_zero(ap, tmp, ptf, &conv);
	}
	else
		conv_no_zero(ap, tmp, ptf, &conv);
	ft_strdel(&conv.prefix);
	ft_strdel(&conv.arg);
	ft_strdel(&conv.field);
	ft_strdel(&conv.preci);
	return (1);
}
