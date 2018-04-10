/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_unicode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 15:16:43 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/28 13:43:43 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	char	*mask_4_octets(unsigned int arg)
{
	char	*new;

	new = NULL;
	if (!(new = ft_memalloc(sizeof(char) * 5)))
		return (NULL);
	new[0] = 240 | (arg >> 18);
	new[1] = 128 | (63 & arg >> 12);
	new[2] = 128 | (63 & arg >> 6);
	new[3] = 128 | (63 & arg);
	new[4] = '\0';
	return (new);
}

static	char	*mask_3_octets(unsigned int arg)
{
	char	*new;

	new = NULL;
	if (!(new = ft_memalloc(sizeof(char) * 4)))
		return (NULL);
	new[0] = 224 | (arg >> 12);
	new[1] = 128 | (63 & arg >> 6);
	new[2] = 128 | (63 & arg);
	new[3] = '\0';
	return (new);
}

static	char	*mask_2_octets(unsigned int arg)
{
	char	*new;

	new = NULL;
	if (!(new = ft_memalloc(sizeof(char) * 3)))
		return (NULL);
	new[0] = 192 | (arg >> 6);
	new[1] = 128 | (63 & arg);
	new[2] = '\0';
	return (new);
}

static	char	*mask_1_octet(unsigned int arg)
{
	char	*new;

	new = NULL;
	if (!(new = ft_memalloc(sizeof(char) * 3)))
		return (NULL);
	new[0] = arg;
	new[1] = '\0';
	return (new);
}

char			*mask_unicode(unsigned int arg)
{
	char	*new;

	new = NULL;
	if (arg < 128)
		new = mask_1_octet(arg);
	else if (arg >= 128 && arg <= 2048)
		new = mask_2_octets(arg);
	else if (arg > 2048 && arg <= 65536)
		new = mask_3_octets(arg);
	else
		new = mask_4_octets(arg);
	return (new);
}
