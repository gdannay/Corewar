/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:41:20 by clegirar          #+#    #+#             */
/*   Updated: 2018/03/16 12:40:06 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		fill_basics_struct(t_parse *new, char *format, int i)
{
	if (format[i] == '+')
		new->plus = 1;
	else if (format[i] == '-')
		new->moins = 1;
	else if (format[i] == ' ')
		new->space = 1;
	else if (format[i] == '0')
		new->zero = 1;
	else if (format[i] == '#')
		new->diez = 1;
	if (format[i] == '+' || format[i] == '-' || format[i] == ' '
			|| format[i] == '0' || format[i] == '#')
		return (1);
	return (0);
}

int		fill_preci_field(t_parse *new, char *format, int *i)
{
	if (format[*i] == '.')
	{
		*i += 1;
		new->precision = ft_atoi(&format[*i]);
		while (format[*i] && ft_isdigit(format[*i]))
			*i += 1;
		*i -= 1;
		return (1);
	}
	else if (ft_isdigit(format[*i]))
	{
		new->size_field = ft_atoi(&format[*i]);
		while (format[*i] && ft_isdigit(format[*i]))
			*i += 1;
		*i -= 1;
		return (1);
	}
	return (0);
}

void	fill_begin(t_parse *new, char *format, int *i)
{
	int		a;

	a = 0;
	if (*i == 0)
	{
		while (format[*i] && format[*i] != '%')
		{
			new->begin = ft_memrealloc(new->begin, ft_strlen(new->begin),
					ft_strlen(new->begin) + 1);
			new->begin[a] = format[*i];
			*i += 1;
			a++;
		}
		if (format[*i])
			*i += 1;
		new->begin = ft_memrealloc(new->begin, ft_strlen(new->begin),
				ft_strlen(new->begin) + 1);
		new->begin[a] = '\0';
	}
	else
		new->begin = NULL;
}

int		chars_modif_len(char c)
{
	if (c != 'l' && c != 'h' && c != 'j' && c != 'z')
		return (0);
	return (1);
}

void	fill_other(t_parse *new, char *format, int *i)
{
	int		a;

	a = 0;
	while (format[*i] && format[*i] != '%')
	{
		new->other = ft_memrealloc(new->other,
				ft_strlen(new->other), ft_strlen(new->other) + 1);
		new->other[a] = format[*i];
		a++;
		*i += 1;
	}
	new->other = ft_memrealloc(new->other,
			ft_strlen(new->other), ft_strlen(new->other) + 1);
	new->other[a] = '\0';
}
