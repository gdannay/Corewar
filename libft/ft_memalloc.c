/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:47:18 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/21 21:38:07 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ap;

	if (size <= 0)
		return (NULL);
	ap = NULL;
	if ((ap = malloc((size))) == NULL)
		return (NULL);
	ft_bzero(ap, size);
	return (ap);
}
