/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 16:59:00 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/24 17:09:41 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	char	**ret;
	int		i;
	int		j;

	i = 0;
	if (!(ret = (char **)ft_memalloc(sizeof(char *) * (ft_tablen(tab) + 1))))
		return (NULL);
	while (tab[i])
	{
		j = 0;
		if (!(ret[i] = (char *)ft_memalloc(ft_strlen(tab[i]) + 1)))
			return (NULL);
		while (tab[i][j])
		{
			ret[i][j] = tab[i][j];
			j++;
		}
		ret[i][j] = '\0';
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
