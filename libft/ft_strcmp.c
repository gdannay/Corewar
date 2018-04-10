/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:44:54 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/14 17:31:40 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	int					i;
	unsigned	char	cs1;
	unsigned	char	cs2;

	i = 0;
	cs1 = (unsigned char)s1[i];
	cs2 = (unsigned char)s2[i];
	while (cs1 && cs2)
	{
		cs1 = (unsigned char)s1[i];
		cs2 = (unsigned char)s2[i];
		if (cs1 != cs2)
			return (cs1 - cs2);
		i++;
	}
	return (cs1 - cs2);
}
