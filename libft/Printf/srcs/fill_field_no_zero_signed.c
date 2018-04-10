/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_field_no_zero_signed.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 16:37:46 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/28 16:52:54 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	fill_field_0_diff(t_parse *tmp, t_conv *conv)
{
	if (conv->moins)
		conv->field = ft_len_dup(tmp->size_field
				- ft_strlen(conv->preci)
				- ft_strlen(conv->arg) - ft_strlen(conv->moins)
				- ft_strlen(conv->space)
				- ft_strlen(conv->plus) + 2, ' ');
	else
		conv->field = ft_len_dup(tmp->size_field
				- ft_strlen(conv->preci)
				- ft_strlen(conv->arg) - ft_strlen(conv->moins)
				- ft_strlen(conv->space)
				- ft_strlen(conv->plus) + 1, ' ');
}

static	void	fill_field_0(t_parse *tmp, t_conv *conv)
{
	if (tmp->precision != 0)
	{
		if (conv->moins)
			conv->field = ft_len_dup(tmp->size_field
					- ft_strlen(conv->preci) - ft_strlen(conv->arg)
					- ft_strlen(conv->space) - ft_strlen(conv->plus)
					- ft_strlen(conv->moins) + 2, ' ');
		else
			conv->field = ft_len_dup(tmp->size_field
					- ft_strlen(conv->preci) - ft_strlen(conv->arg)
					- ft_strlen(conv->space) - ft_strlen(conv->plus)
					- ft_strlen(conv->moins) + 1, ' ');
	}
	else
	{
		if (conv->moins)
			conv->field = ft_len_dup(tmp->size_field
					- ft_strlen(conv->preci) - ft_strlen(conv->space)
					- ft_strlen(conv->plus) - ft_strlen(conv->moins) + 2, ' ');
		else
			conv->field = ft_len_dup(tmp->size_field
					- ft_strlen(conv->preci)
					- ft_strlen(conv->space) - ft_strlen(conv->plus)
					- ft_strlen(conv->moins) + 1, ' ');
	}
}

void			fill_field_no_zero_signed(t_parse *tmp, t_printf *ptf,
		t_conv *conv)
{
	if (ptf->nb != 0)
		fill_field_0_diff(tmp, conv);
	else
		fill_field_0(tmp, conv);
}
