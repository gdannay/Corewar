/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 15:27:13 by clegirar          #+#    #+#             */
/*   Updated: 2018/03/16 12:36:42 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	stock_struct(t_parse *new)
{
	new->plus = -1;
	new->moins = -1;
	new->space = -1;
	new->zero = -1;
	new->precision = -1;
	new->size_field = -1;
	new->diez = -1;
}

static	void	check_other(t_parse *new, char *format, int ret, int *i)
{
	if (*i + 1 < (int)ft_strlen(format))
	{
		if (ret == 0)
			*i += 1;
		if (format[*i] && format[*i] != '%')
			fill_other(new, format, i);
	}
	else if (format[*i] && ret != 0)
		fill_other(new, format, i);
}

static	t_parse	*new_maillon(char *format, int *i)
{
	t_parse	*new;
	int		ret;

	new = NULL;
	if (!(new = (t_parse *)ft_memalloc(sizeof(t_parse))))
		return (NULL);
	stock_struct(new);
	fill_begin(new, format, i);
	while (format[*i] && (ret = mng_flags(new, format, *i)))
	{
		if (fill_basics_struct(new, format, *i)
				|| fill_preci_field(new, format, i)
				|| fill_modif_len(new, format, i))
			*i += 1;
		else
			break ;
	}
	check_other(new, format, ret, i);
	new->next = NULL;
	return (new);
}

t_parse			*create_list(char *format)
{
	int		i;
	t_parse	*lst;
	t_parse	*tmp;
	t_parse	*tmp2;

	i = 0;
	if (format[i] == '%')
		i++;
	tmp = new_maillon(format, &i);
	lst = tmp;
	tmp2 = tmp;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			tmp = new_maillon(format, &i);
			tmp2->next = tmp;
			tmp2 = tmp;
		}
		else
			i++;
	}
	return (lst);
}
