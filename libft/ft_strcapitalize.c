/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 18:00:28 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 19:21:56 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcapitalize(char *str)
{
	int		i;

	i = 0;
	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] = str[0] - 32;
	while (str[i])
	{
		if ((str[i - 1] < 'a' || str[i - 1] > 'z')
				|| (str[i - 1] < 'A' || str[i - 1] > 'Z'))
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] = str[i] - 32;
		}
		if ((str[i - 1] >= 'a' && str[i - 1] <= 'z')
				|| (str[i - 1] >= 'A' && str[i - 1] <= 'Z')
				|| (str[i - 1] >= '0' && str[i - 1] <= '9'))
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				str[i] = str[i] + 32;
		}
		i++;
	}
	return (str);
}
