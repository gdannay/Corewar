/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 15:49:31 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 15:53:27 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_vprintf(const char *format, va_list ap)
{
	int			ret;
	t_parse		*lst;
	t_printf	ptf;

	if (!format[0])
		return (0);
	if (!(lst = create_list((char *)format)))
		return (-1);
	ret = algo(ap, lst, &ptf);
	if (ret == -1)
		return (-1);
	ft_putstr(ptf.buff);
	del_list(&lst);
	return (ret);
}

int		ft_vsprintf(char *str, const char *format, va_list ap)
{
	int			ret;
	t_parse		*lst;
	t_printf	ptf;

	if (!format[0])
		return (0);
	if (!(lst = create_list((char *)format)))
		return (-1);
	ret = algo(ap, lst, &ptf);
	if (ret == -1)
		return (-1);
	ft_strcpy(str, ptf.buff);
	del_list(&lst);
	return (ret);
}

int		ft_vsnprintf(char *str, size_t size, const char *format, va_list ap)
{
	int			ret;
	t_parse		*lst;
	t_printf	ptf;

	if (!format[0])
		return (0);
	if (!(lst = create_list((char *)format)))
		return (-1);
	ret = algo(ap, lst, &ptf);
	if (ret == -1)
		return (-1);
	ft_strncpy(str, ptf.buff, size);
	del_list(&lst);
	return (ret);
}
