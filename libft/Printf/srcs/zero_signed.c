/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero_signed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:35:41 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/28 16:38:31 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	fill_moins_plus_preci(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	if (conv->arg[0] == '-')
		conv->moins = ft_strdup("-");
	if (tmp->space > 0 && ptf->nb >= 0 && tmp->plus < 0)
		conv->space = ft_strdup(" ");
	if (tmp->plus > 0 && ptf->nb >= 0)
		conv->plus = ft_strdup("+");
	if (tmp->precision > 0)
	{
		if (conv->moins)
			conv->preci = ft_len_dup(tmp->precision
					- ft_strlen(conv->arg) + 2, '0');
		else
			conv->preci = ft_len_dup(tmp->precision
					- ft_strlen(conv->arg) + 1, '0');
	}
}

static	void	fill_field(t_parse *tmp, t_conv *conv)
{
	if (tmp->size_field > 0)
	{
		if (conv->moins)
			conv->field = ft_len_dup(tmp->size_field - ft_strlen(conv->preci)
					- ft_strlen(conv->arg) - ft_strlen(conv->moins)
					- ft_strlen(conv->space) - ft_strlen(conv->plus) + 2, '0');
		else
			conv->field = ft_len_dup(tmp->size_field - ft_strlen(conv->preci)
					- ft_strlen(conv->arg) - ft_strlen(conv->moins)
					- ft_strlen(conv->space) - ft_strlen(conv->plus) + 1, '0');
	}
}

void			conv_zero_signed(t_parse *tmp, t_printf *ptf, t_conv *conv)
{
	fill_moins_plus_preci(tmp, ptf, conv);
	fill_field(tmp, conv);
	fill_count_buff(ptf, conv->moins, ft_strlen(conv->moins));
	fill_count_buff(ptf, conv->space, ft_strlen(conv->space));
	fill_count_buff(ptf, conv->plus, ft_strlen(conv->plus));
	fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
	fill_count_buff(ptf, conv->preci, ft_strlen(conv->preci));
	if (ptf->nb > 0)
	{
		if (conv->moins)
			fill_count_buff(ptf, conv->arg + 1, ft_strlen(conv->arg) - 1);
		else
			fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	}
	else
	{
		if (tmp->precision != 0)
		{
			if (conv->moins)
				fill_count_buff(ptf, conv->arg + 1, ft_strlen(conv->arg) - 1);
			else
				fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
		}
	}
}
