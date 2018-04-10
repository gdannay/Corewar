/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 14:43:10 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 15:49:23 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_snprintf(char *str, size_t size, const char *format, ...)
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
	ft_strncpy(str, ptf.buff, size);
	del_list(&lst);
	va_end(ap);
	return (ret);
}

int		ft_sprintf(char *str, const char *format, ...)
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
	ft_strcpy(str, ptf.buff);
	del_list(&lst);
	va_end(ap);
	return (ret);
}
