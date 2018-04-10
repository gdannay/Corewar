/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:44:34 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/14 21:21:36 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest && dest[i])
		i++;
	j = 0;
	while (src && src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}
