/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:49:22 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:39:09 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strequ(char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] && s2[j])
	{
		if (s1[i] != s2[j])
			return (0);
		i++;
		j++;
	}
	if (s1[i] == '\0' && s2[j] == '\0')
		return (1);
	return (0);
}
