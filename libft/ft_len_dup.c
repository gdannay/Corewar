/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:54:35 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 16:55:58 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_len_dup(int n, char c)
{
	char	*str;
	int		i;

	if (!(str = (char *)ft_memalloc(sizeof(char) * (n + 1))))
		return (NULL);
	i = 0;
	while (i < n - 1)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}
