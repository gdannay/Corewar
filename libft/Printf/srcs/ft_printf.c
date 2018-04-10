/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:43:04 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 14:39:16 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	int			ret;
	va_list		ap;
	t_parse		*lst;
	t_printf	ptf;

	if (!format[0])
		return (0);
	va_start(ap, format);
	if (!(lst = create_list((char *)format)))
		return (-1);
	ret = algo(ap, lst, &ptf);
	if (ret == -1)
		return (-1);
	ft_putstr(ptf.buff);
	del_list(&lst);
	va_end(ap);
	return (ret);
}
