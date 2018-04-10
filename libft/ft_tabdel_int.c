/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 16:51:38 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/30 22:52:05 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	int_del(int **tab)
{
	if (!tab || !*tab)
		return ;
	free(*tab);
	*tab = NULL;
}

void	ft_tabdel_int(int ***tab)
{
	size_t	i;
	int		**erase;

	erase = NULL;
	if (!tab || !*tab)
		return ;
	i = 0;
	erase = *tab;
	while (erase[i])
	{
		int_del(&erase[i]);
		i++;
	}
	free(*tab);
	*tab = NULL;
}
