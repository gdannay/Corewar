/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 21:08:49 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 16:55:54 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	aff_char(t_printf *ptf, char arg_c, char *field, int c)
{
	ft_putstr(ptf->buff);
	if (c == 1 && field)
		ft_putstr(field);
	ft_putchar(arg_c);
	if (c == 0 && field)
		ft_putstr(field);
	ptf->surplus += 1 + ft_strlen(field) + ft_strlen(ptf->buff);
	ft_bzero(ptf->buff, BUFFER + 1);
	ptf->cursor = 0;
}

static	void	aff_unicode(t_parse *tmp, t_printf *ptf,
		char arg_c, char *new)
{
	char	c;
	char	*field;

	field = NULL;
	c = (tmp->zero > 0) ? '0' : ' ';
	if (tmp->size_field > 0)
		field = ft_len_dup(tmp->size_field - ft_strlen(new) + 1, c);
	if (tmp->moins > 0)
	{
		if (new)
			fill_count_buff(ptf, new, ft_strlen(new));
		else
			aff_char(ptf, arg_c, NULL, 3);
		fill_count_buff(ptf, field, ft_strlen(field));
	}
	else
	{
		fill_count_buff(ptf, field, ft_strlen(field));
		if (new)
			fill_count_buff(ptf, new, ft_strlen(new));
		else
			aff_char(ptf, arg_c, NULL, 3);
	}
	ft_strdel(&field);
}

static	int		carac_unicode(va_list ap, t_parse *tmp, t_printf *ptf)
{
	unsigned	int	arg;
	char			*new;
	char			arg_c;

	arg_c = '\0';
	new = NULL;
	arg = va_arg(ap, unsigned int);
	if (arg < 128)
		arg_c = arg;
	else
		new = mask_unicode(arg);
	aff_unicode(tmp, ptf, arg_c, new);
	ft_strdel(&new);
	return (1);
}

int				conv_char(va_list ap, t_parse *tmp, t_printf *ptf)
{
	char	arg;
	char	*field;
	char	c;

	field = NULL;
	if (tmp->flag == 'C'
			|| (tmp->modif_len && ft_strcmp(tmp->modif_len, "l") == 0))
	{
		carac_unicode(ap, tmp, ptf);
		return (0);
	}
	arg = va_arg(ap, int);
	c = (tmp->zero > 0) ? '0' : ' ';
	if (tmp->size_field > 0)
		field = ft_len_dup(tmp->size_field, c);
	if (tmp->moins > 0)
		aff_char(ptf, arg, field, 0);
	else
		aff_char(ptf, arg, field, 1);
	ft_strdel(&field);
	return (1);
}
