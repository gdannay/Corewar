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
	int					registre[REG_NUMBER];
	int					numero_who_create_process;
	int 				position;
	int					live;
	char				carry;
	char				*pc;
	int					cycle;
	struct s_process	*next;
	struct s_process  *prev;
}						t_process;

typedef struct			s_player
{
	header_t			*header;
	char					*code;
	int 					numero;
	int						global_live;
	int						last_live;
	struct s_player		*next;
}						t_player;

typedef struct			s_vm
{
	char				*arena;
	long				cycle;
	int					cycle_to_die;
	int					cycle_delta;
	int					nbr_live;
	unsigned long		process;
}						t_vm;

typedef struct 		s_map
{
	struct s_player		*player;
	struct s_vm	*vm;
	struct s_process	*process;
}									t_map;

uint32_t				swap_32_bytes(uint32_t nb);
void					free_players(t_player **first);
int						read_file(t_player **first, int fd, char *name);
void					*header_error(header_t *header, char *str, char *name);
int						code_error(t_player **first, char *str, char *name);
//int					execute_code(t_player *first);
char					*create_arena(t_player *first);
void 					visu(char *arena, t_player *first);
t_player *read_av(char **av, int ac);
int recup_int(char *str);
t_vm *create_vm(t_player *first);
t_process *initialize_process(t_player *player);
int	nbr_players(t_player *first);
void run_vm(t_map *map);

int instruction_live(t_vm *vm, t_process *process, t_player *player);
int instruction_ld(t_vm *vm, t_process *process);
int instruction_st(t_vm *vm, t_process *process);
int instruction_add(t_vm *vm, t_process *process);
int instruction_sub(t_vm *vm, t_process *process);

char *take_opcode(unsigned char c, char *str);
void take_params(char *arena, int pos, int *params, char *str, int unknown);
int recup_nb_32(char *arena, int position);
int recup_nb_16(char *arena, int position);
void write_in_arena_32(char *arena, int registre, int pos);
t_process	*create_process(t_process **process, t_process *tmp, int pos, int player_numero);
#endif
