/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:44:45 by clegirar          #+#    #+#             */
/*   Updated: 2018/04/10 17:02:27 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint32_t	swap_32_bytes(uint32_t nb)
{
	nb = (nb << 24) | ((nb << 8) & BIT_2)
		| (nb >> 24) | ((nb >> 8) & BIT_3);
	return (nb);
}

int	main(void)
{

	/*header_t	*head;
	struct stat	buf;
	head = (header_t *)malloc(sizeof(header_t));

	head->magic = swap_32_bytes((uint32_t)COREWAR_EXEC_MAGIC);
	strcpy(head->prog_name, "emtagueule");
	head->prog_size = swap_32_bytes(5);
	strcpy(head->comment, "Tufaiclem");
	write(1, head, sizeof(*head));*/
	return (0);
}
