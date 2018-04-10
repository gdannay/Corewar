/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:50:17 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:48:38 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] && s2[j] && i < n)
	{
		if (s1[i] != s2[j])
			return (0);
		i++;
		j++;
	}
	if ((s1[i] == '\0' && s2[j] == '\0') || (i == n && j == n))
		return (1);
	return (0);
}
