/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:19:34 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/28 14:25:36 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	t_flags	g_flags[] =
{
	{'s'},
	{'S'},
	{'p'},
	{'d'},
	{'i'},
	{'D'},
	{'u'},
	{'o'},
	{'O'},
	{'U'},
	{'x'},
	{'X'},
	{'b'},
	{'c'},
	{'C'},
	{'f'},
	{'%'},
};

int				flag_mod(char c)
{
	int		a;

	a = 0;
	while (g_flags[a].c)
	{
		if (c == g_flags[a].c)
			return (1);
		a++;
	}
	return (0);
}

int				mng_flags(t_parse *new, char *format, int i)
{
	int		a;

	a = 0;
	while (g_flags[a].c)
	{
		if (format[i] == g_flags[a].c)
		{
			new->flag = g_flags[a].c;
			return (0);
		}
		a++;
	}
	if (ft_isalpha(format[i]) && !chars_modif_len(format[i]))
	{
		new->flag = format[i];
		return (-1);
	}
	return (1);
}
