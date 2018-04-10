/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:35:13 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 15:54:11 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dprintf(int fd, const char *format, ...)
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
	ft_putstr_fd(ptf.buff, fd);
	del_list(&lst);
	va_end(ap);
	return (ret);
}
