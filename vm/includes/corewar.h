/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:07:18 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/09 10:51:01 by clegirar         ###   ########.fr       */
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
# include <ncurses.h>

# define HEADER_SIZE sizeof(header_t)
#

typedef struct			s_process
{
	int					live;
	char				carry;
	char				*pc;
	int					cycle;
	struct s_process	*next;
}						t_process;

typedef struct			s_player
{
	header_t			*header;
	char				*code;
	t_process			*process;
	int					global_live;
	int					last_live;
	struct s_player		*next;
}						t_player;

typedef struct			s_machine
{
	char				*arena;
	long				cycle;
	int					cycle_to_die;
	int					cycle_delta;
	int					nbr_live;
	unsigned long		process;
}						t_machine;

uint32_t				swap_32_bytes(uint32_t nb);
void					free_players(t_player **first);
int						read_file(t_player **first, int fd, char *name);
void					*header_error(header_t *header, char *str, char *name);
int						code_error(t_player **first, char *str, char *name);
//int					execute_code(t_player *first);
char					*create_arena(t_player *first);
void 					visu(char *arena, t_player *first);

#endif
