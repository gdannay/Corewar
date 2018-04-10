/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 14:26:07 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/28 14:45:56 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int		ll_l(char *str, char **ret)
{
	if (ft_strstr(str, "ll"))
	{
		if ((ft_strstr(str, "j"))
				|| (ft_strstr(str, "z"))
				|| (ft_strstr(str, "h")))
			*ret = ft_strdup("ll");
		else
			return (0);
		return (1);
	}
	else if (ft_strstr(str, "l"))
	{
		if ((ft_strstr(str, "ll"))
				|| (ft_strstr(str, "j"))
				|| (ft_strstr(str, "z"))
				|| (ft_strstr(str, "h")))
			*ret = ft_strdup("l");
		else
			return (0);
		return (1);
	}
	return (-1);
}

static	int		j_z(char *str, char **ret)
{
	if (ft_strstr(str, "j"))
	{
		if ((ft_strstr(str, "l"))
				|| (ft_strstr(str, "z"))
				|| (ft_strstr(str, "h")))
			*ret = ft_strdup("j");
		else
			return (0);
		return (1);
	}
	else if (ft_strstr(str, "z"))
	{
		if ((ft_strstr(str, "l"))
				|| (ft_strstr(str, "j"))
				|| (ft_strstr(str, "h")))
			*ret = ft_strdup("z");
		else
			return (0);
		return (1);
	}
	return (-1);
}

static	int		hh_h(char *str, char **ret)
{
	if (ft_strstr(str, "hh"))
	{
		if ((ft_strstr(str, "l"))
				|| (ft_strstr(str, "j"))
				|| (ft_strstr(str, "z")))
			*ret = ft_strdup("l");
		else
			return (0);
		return (1);
	}
	else if (ft_strstr(str, "h"))
	{
		if ((ft_strstr(str, "l"))
				|| (ft_strstr(str, "j"))
				|| (ft_strstr(str, "z")))
			*ret = ft_strdup("l");
		else
			return (0);
		return (1);
	}
	return (-1);
}

static	char	*check_modif_len(char *str)
{
	int		i;
	int		r;
	int		r1;
	int		r2;
	char	*ret;

	ret = NULL;
	i = 0;
	while (str[i])
	{
		r = ll_l(str, &ret);
		r1 = j_z(str, &ret);
		r2 = hh_h(str, &ret);
		if (r == 0 || r1 == 0 || r2 == 0)
			return (str);
		else if (r == 1 || r1 == 1 || r2 == 1)
			break ;
		i++;
	}
	ft_strdel(&str);
	return (ret);
}

int				fill_modif_len(t_parse *new, char *format, int *i)
{
	int		a;

	a = 0;
	if (format[*i] && chars_modif_len(format[*i]))
	{
		while (format[*i] && chars_modif_len(format[*i])
				&& mng_flags(new, format, *i))
		{
			new->modif_len = ft_memrealloc(new->modif_len,
					ft_strlen(new->modif_len), ft_strlen(new->modif_len) + 1);
			new->modif_len[a] = format[*i];
			a++;
			*i += 1;
		}
		new->modif_len = ft_memrealloc(new->modif_len,
				ft_strlen(new->modif_len), ft_strlen(new->modif_len) + 1);
		new->modif_len[a] = '\0';
		new->modif_len = check_modif_len(new->modif_len);
		*i -= 1;
		return (1);
	}
	return (0);
}
