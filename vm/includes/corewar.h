/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:07:18 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/04 16:12:40 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include "../../libft/libft.h"
# include "../../op/op.h"
# include "../../asm/includes/asm.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

# define HEADER_SIZE sizeof(header_t)

typedef struct		s_player
{
	header_t		*header;
	char			*code;
	struct s_player	*next;
}					t_player;

uint32_t			swap_32_bytes(uint32_t nb);
void				free_players(t_player **first);
int					read_file(t_player **first, int fd, char *name);
void				*header_error(header_t *header, char *str, char *name);
int					code_error(t_player **first, char *str, char *name);
int					execute_code(t_player *first);

#endif
