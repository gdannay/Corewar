/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:47:27 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/15 18:40:48 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabcpy(char **tab, int i)
{
	char	**ret;
	int		j;

	if (!(ret = (char **)ft_memalloc(sizeof(char *)
					* (ft_tablen(tab) + 1 - i))))
		return (NULL);
	j = 0;
	while (tab[i])
		ret[j++] = ft_strdup(tab[i++]);
	ret[j] = NULL;
	return (ret);
}
