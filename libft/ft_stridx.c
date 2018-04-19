/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stridx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:39:45 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/17 19:04:55 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_stridx(char *str, char *cmp)
{
	char	*tmp;

	if (str == NULL)
		return (0);
	if ((tmp = ft_strstr(str, cmp)) == NULL)
		return (ft_strlen(str));
	return (tmp - str);
}
