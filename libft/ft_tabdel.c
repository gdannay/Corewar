/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 16:45:28 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/30 22:51:51 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_tabdel(char ***tab)
{
	size_t	i;
	char	**erase;

	erase = NULL;
	if (!tab || !*tab)
		return ;
	i = 0;
	erase = *tab;
	while (erase[i])
	{
		ft_strdel(&erase[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}
