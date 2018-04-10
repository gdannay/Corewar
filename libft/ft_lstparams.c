/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstparams.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 13:58:45 by clegirar          #+#    #+#             */
/*   Updated: 2017/11/09 14:53:40 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstparams(int ac, char **av)
{
	t_list	*ret;
	t_list	*tmp;
	int		i;

	i = 0;
	if (!(tmp = ft_lstnew(av[i], ft_strlen(av[i]))))
		return (NULL);
	ret = tmp;
	i++;
	while (i < ac)
	{
		if (!(tmp->next = ft_lstnew(av[i], ft_strlen(av[i]))))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}
