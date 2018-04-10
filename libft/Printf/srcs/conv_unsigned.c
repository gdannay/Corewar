/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 21:14:50 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 17:49:17 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*fill_arg(va_list ap, t_parse *tmp, int base, char c)
{
	char	*arg;

	arg = NULL;
	if (tmp->modif_len && tmp->flag != 'O' && tmp->flag != 'U')
	{
		if (ft_strcmp(tmp->modif_len, "hh") == 0)
			arg = ft_lltoa_base((unsigned char)
					va_arg(ap, unsigned long long), base, c);
		else if (ft_strcmp(tmp->modif_len, "h") == 0)
			arg = ft_lltoa_base((unsigned short)
					va_arg(ap, unsigned long long), base, c);
		else if ((ft_strcmp(tmp->modif_len, "l") == 0)
				|| (ft_strcmp(tmp->modif_len, "ll") == 0)
				|| (ft_strcmp(tmp->modif_len, "j") == 0)
				|| (ft_strcmp(tmp->modif_len, "z") == 0))
			arg = ft_lltoa_base((unsigned long long)
					va_arg(ap, unsigned long long), base, c);
	}
	else if (tmp->flag != 'O' && tmp->flag != 'U')
		arg = ft_lltoa_base((unsigned int)va_arg(ap, unsigned int), base, c);
	else if (tmp->flag == 'O')
		arg = ft_lltoa_base(va_arg(ap, unsigned long long), base, c);
	else if (tmp->flag == 'U')
		arg = ft_lltoa_base(va_arg(ap, unsigned long long), base, c);
	return (arg);
}

static	char	*fill_arg_base(va_list ap, t_parse *tmp, t_printf *ptf)
{
	char	*arg;
	int		base;
	char	c;

	arg = NULL;
	c = 'a';
	base = 10;
	if (tmp->flag == 'o' || tmp->flag == 'O')
		base = 8;
	else if (tmp->flag == 'x' || tmp->flag == 'X')
		base = 16;
	else if (tmp->flag == 'b')
		base = 2;
	if (tmp->flag == 'X')
		c = 'A';
	arg = fill_arg(ap, tmp, base, c);
	ptf->nbl = ft_atoll_base(arg, base, c);
	return (arg);
}

int				conv_unsigned(va_list ap, t_parse *tmp, t_printf *ptf)
{
	t_conv	conv;

	conv.diez = NULL;
	conv.arg = NULL;
	conv.field = NULL;
	conv.preci = NULL;
	conv.arg = fill_arg_base(ap, tmp, ptf);
	if (tmp->zero > 0)
	{
		if (tmp->moins > 0 || tmp->precision >= 0)
			conv_no_zero_unsigned(tmp, ptf, &conv);
		else
			conv_zero_unsigned(tmp, ptf, &conv);
	}
	else
		conv_no_zero_unsigned(tmp, ptf, &conv);
	ft_strdel(&conv.diez);
	ft_strdel(&conv.arg);
	ft_strdel(&conv.field);
	ft_strdel(&conv.preci);
	return (1);
}
