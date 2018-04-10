/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 18:11:07 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/28 18:55:26 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_ptr_fct	g_ptr_fct[] =
{
	{'x', &conv_unsigned},
	{'X', &conv_unsigned},
	{'o', &conv_unsigned},
	{'O', &conv_unsigned},
	{'b', &conv_unsigned},
	{'u', &conv_unsigned},
	{'U', &conv_unsigned},
	{'D', &conv_signed},
	{'d', &conv_signed},
	{'i', &conv_signed},
	{'s', &conv_string},
	{'S', &conv_string},
	{'c', &conv_char},
	{'C', &conv_char},
	{'f', &conv_float},
	{'p', &conv_pointeur},
	{'%', &conv_mod},
};

static	int		check_flags(va_list ap, t_parse *tmp, t_printf *ptf)
{
	int		i;

	i = 0;
	while (g_ptr_fct[i].c)
	{
		if (tmp->flag == g_ptr_fct[i].c)
		{
			g_ptr_fct[i].f(ap, tmp, ptf);
			return (1);
		}
		i++;
	}
	return (0);
}

static	void	no_flag_space(t_parse *tmp, t_printf *ptf, char *field)
{
	if (tmp->size_field > 0)
		field = ft_len_dup(tmp->size_field, ' ');
	if (tmp->moins > 0)
	{
		if (tmp->flag)
			fill_count_buff(ptf, &tmp->flag, 1);
		if (field)
			fill_count_buff(ptf, field, ft_strlen(field));
	}
	else
	{
		if (field)
			fill_count_buff(ptf, field, ft_strlen(field));
		if (tmp->flag)
			fill_count_buff(ptf, &tmp->flag, 1);
	}
}

static	void	no_flag(t_parse *tmp, t_printf *ptf)
{
	char	*field;
	char	c;

	field = NULL;
	c = ' ';
	if (tmp->zero > 0 && tmp->moins < 0)
		c = '0';
	if (c == '0')
	{
		if (tmp->size_field > 0)
			field = ft_len_dup(tmp->size_field, '0');
		if (field)
			fill_count_buff(ptf, field, ft_strlen(field));
		if (tmp->flag)
			fill_count_buff(ptf, &tmp->flag, 1);
	}
	else
		no_flag_space(tmp, ptf, field);
	ft_strdel(&field);
}

int				algo(va_list ap, t_parse *lst, t_printf *ptf)
{
	t_parse		*tmp;

	ft_bzero(ptf->buff, BUFFER + 1);
	tmp = lst;
	ptf->surplus = 0;
	ptf->cursor = 0;
	while (tmp)
	{
		if (tmp->begin && c_bu(ptf, tmp->begin))
			(void)ft_strcat(ptf->buff, tmp->begin);
		if (check_flags(ap, tmp, ptf) == 0 && tmp->flag)
			no_flag(tmp, ptf);
		if (tmp->other && tmp->flag != tmp->other[0] && c_bu(ptf, tmp->other))
			(void)ft_strcat(ptf->buff, tmp->other);
		else if (tmp->other && tmp->flag == tmp->other[0]
				&& flag_mod(tmp->flag))
			(void)ft_strcat(ptf->buff, tmp->other);
		else if (tmp->other && tmp->flag == tmp->other[0]
				&& c_bu(ptf, tmp->other + 1))
			(void)ft_strcat(ptf->buff, tmp->other + 1);
		tmp = tmp->next;
	}
	return (ft_strlen(ptf->buff) + ptf->surplus);
}
