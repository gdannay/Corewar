/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_string_unicode.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:34:47 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/28 14:03:58 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	fill_conv(t_parse *tmp, t_conv *conv, unsigned int *arg)
{
	int				i;
	int				j;
	int				k;

	i = 0;
	j = 0;
	k = 0;
	if (!arg)
		conv->ret = ft_strdup("(null)");
	while (arg && arg[i])
	{
		conv->new = mask_unicode(arg[i]);
		if (tmp->precision == -1
				|| k + (int)ft_strlen(conv->new) <= tmp->precision)
		{
			conv->ret = ft_memrealloc(conv->ret, ft_strlen(conv->ret),
					ft_strlen(conv->ret) + ft_strlen(conv->new));
			conv->ret = ft_strcat(conv->ret, conv->new);
			j += ft_strlen(conv->new);
			conv->ret[j] = '\0';
		}
		k += ft_strlen(conv->new);
		ft_strdel(&conv->new);
		i++;
	}
}

static	void	fill_buff(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	conv->c = (tmp->zero > 0) ? '0' : ' ';
	if (tmp->size_field > 0)
	{
		if (tmp->precision != 0)
			conv->field = ft_len_dup(tmp->size_field
					- ft_strlen(conv->ret) + 1, conv->c);
		else
			conv->field = ft_len_dup(tmp->size_field + 1, conv->c);
	}
	if (tmp->moins > 0)
	{
		if (tmp->precision != 0)
			fill_count_buff(ptf, conv->ret, ft_strlen(conv->ret));
		fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
	}
	else
	{
		fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
		if (tmp->precision != 0)
			fill_count_buff(ptf, conv->ret, ft_strlen(conv->ret));
	}
}

int				string_unicode(va_list ap, t_parse *tmp, t_printf *ptf)
{
	unsigned	int	*arg;
	t_conv			conv;

	conv.new = NULL;
	conv.ret = NULL;
	conv.field = NULL;
	arg = va_arg(ap, unsigned int *);
	fill_conv(tmp, &conv, arg);
	fill_buff(tmp, ptf, &conv);
	ft_strdel(&conv.new);
	ft_strdel(&conv.ret);
	ft_strdel(&conv.field);
	return (1);
}
