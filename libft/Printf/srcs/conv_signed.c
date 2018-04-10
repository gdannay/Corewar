/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_signed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 21:14:18 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/28 15:41:02 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*fill_arg(va_list ap, t_parse *tmp, t_printf *ptf)
{
	char	*arg;

	arg = NULL;
	if (tmp->modif_len && tmp->flag != 'D')
	{
		if (ft_strcmp(tmp->modif_len, "hh") == 0)
			arg = ft_lltoa_signed((char)va_arg(ap, long long));
		else if (ft_strcmp(tmp->modif_len, "h") == 0)
			arg = ft_lltoa_signed((short)va_arg(ap, long long));
		else if ((ft_strcmp(tmp->modif_len, "l") == 0)
				|| (ft_strcmp(tmp->modif_len, "ll") == 0)
				|| (ft_strcmp(tmp->modif_len, "j") == 0)
				|| (ft_strcmp(tmp->modif_len, "z") == 0))
			arg = ft_lltoa_signed((long long)va_arg(ap, long long));
	}
	else if (tmp->flag != 'D')
		arg = ft_lltoa_signed((int)va_arg(ap, long long));
	else if (tmp->flag == 'D')
		arg = ft_lltoa_signed((long long)va_arg(ap, long long));
	ptf->nb = ft_atol_signed(arg);
	return (arg);
}

int				conv_signed(va_list ap, t_parse *tmp, t_printf *ptf)
{
	t_conv	conv;

	conv.space = NULL;
	conv.plus = NULL;
	conv.field = NULL;
	conv.arg = NULL;
	conv.preci = NULL;
	conv.moins = NULL;
	conv.arg = fill_arg(ap, tmp, ptf);
	if (tmp->zero > 0)
	{
		if (tmp->moins > 0 || tmp->precision >= 0)
			conv_no_zero_signed(tmp, ptf, &conv);
		else
			conv_zero_signed(tmp, ptf, &conv);
	}
	else
		conv_no_zero_signed(tmp, ptf, &conv);
	ft_strdel(&conv.space);
	ft_strdel(&conv.plus);
	ft_strdel(&conv.field);
	ft_strdel(&conv.arg);
	ft_strdel(&conv.preci);
	ft_strdel(&conv.moins);
	return (1);
}
