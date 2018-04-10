/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 21:18:01 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 14:56:17 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*ft_strndup_printf(const char *s, int n)
{
	char	*ret;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	if (n <= 0)
		n = ft_strlen(s);
	if (!(ret = ft_memalloc(n + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && i < n)
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (ret);
}

static	void	fill_conv(va_list ap, t_parse *tmp, t_conv *conv)
{
	char	*ap_arg;

	if (!(ap_arg = ft_strdup(va_arg(ap, char *))))
		conv->arg = ft_strndup_printf("(null)", tmp->precision);
	else
		conv->arg = ft_strndup_printf(ap_arg, tmp->precision);
	conv->c = ' ';
	if (tmp->moins < 0)
		conv->c = (tmp->zero > 0) ? '0' : ' ';
	if (tmp->size_field > 0)
	{
		if (tmp->precision != 0)
			conv->field = ft_len_dup(tmp->size_field
					- ft_strlen(conv->arg) + 1, conv->c);
		else
			conv->field = ft_len_dup(tmp->size_field + 1, conv->c);
	}
	ft_strdel(&ap_arg);
}

static	void	fill_buff(t_printf *ptf, t_parse *tmp, t_conv *conv)
{
	if (tmp->moins > 0)
	{
		if (tmp->precision != 0)
			fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
		fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
	}
	else
	{
		fill_count_buff(ptf, conv->field, ft_strlen(conv->field));
		if (tmp->precision != 0)
			fill_count_buff(ptf, conv->arg, ft_strlen(conv->arg));
	}
}

int				conv_string(va_list ap, t_parse *tmp, t_printf *ptf)
{
	t_conv	conv;

	conv.field = NULL;
	conv.preci = NULL;
	conv.arg = NULL;
	if (tmp->flag == 'S'
			|| (tmp->modif_len && ft_strcmp(tmp->modif_len, "l") == 0))
	{
		string_unicode(ap, tmp, ptf);
		return (0);
	}
	fill_conv(ap, tmp, &conv);
	fill_buff(ptf, tmp, &conv);
	ft_strdel(&conv.preci);
	ft_strdel(&conv.arg);
	ft_strdel(&conv.field);
	return (1);
}
