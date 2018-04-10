/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:53:37 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:51:41 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrev(char *str)
{
	int		i;
	int		len;
	char	s;

	len = 0;
	while (str[len])
		len++;
	i = 0;
	while (i < len / 2)
	{
		s = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = s;
		i++;
	}
	return (str);
}
