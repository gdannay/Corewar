/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 09:57:40 by vferreir          #+#    #+#             */
/*   Updated: 2017/12/05 17:09:57 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoindel(char const *s1, char const *s2)
{
	char	*cast1;
	char	*cast2;
	char	*new;
	int		i;
	int		t;

	cast1 = (char *)s1;
	cast2 = (char *)s2;
	if (!(new = (char *)malloc(sizeof(char) *
					(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	i = 0;
	t = 0;
	while (cast1 != NULL && cast1[t])
		new[i++] = cast1[t++];
	t = 0;
	while (cast2 != NULL && cast2[t])
		new[i++] = cast2[t++];
	new[i] = '\0';
	free(cast1);
	return (new);
}
