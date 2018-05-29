/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:07:18 by gdannay           #+#    #+#             */
/*   Updated: 2018/05/29 15:38:12 by clegirar         ###   ########.fr       */
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

typedef struct			s_process
{
	int					registre[REG_NUMBER];
	int					numero_who_create_process;
	int 				position;
	int					live;
	char				carry;
	int					cycle;
	char				inst;
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
	int						start;
	struct s_player		*next;
	struct s_player		*prev;
}						t_player;

typedef struct			s_vm
{
	char				*arena;
	char				*arena_player;
	unsigned long long				cycle;
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

typedef	struct		s_ptr
{
	int							current;
	int							(*f)(t_vm *vm, t_process *process);
}					t_ptr;

uint32_t				swap_32_bytes(uint32_t nb);
int						read_file(t_player **first, int fd, char *name);
void					*header_error(header_t *header, char *str, char *name);
int						code_error(char *buff, t_player **player, char *str, char *name);
char					*create_arena(t_player *first);
void 					print_arena(WINDOW *visu, t_vm *vm, char *arena, t_map *map);
void 					print_infos(WINDOW *infos, t_map *map);
t_player *read_av(char **av, int ac);
int recup_int(char *str);
t_vm *create_vm(t_player *first);
t_process *initialize_process(t_player *player);
int	nbr_players(t_player *first);
int run_vm(t_map *map);

int instruction_live(t_vm *vm, t_process *process, t_player *player);
int instruction_ld(t_vm *vm, t_process *process);
int instruction_lld(t_vm *vm, t_process *process);
int instruction_lldi(t_vm *vm, t_process *process);
int instruction_st(t_vm *vm, t_process *process);
int instruction_add(t_vm *vm, t_process *process);
int instruction_sub(t_vm *vm, t_process *process);
int instruction_and(t_vm *vm, t_process *process);
int	instruction_or(t_vm *vm, t_process *process);
int	instruction_xor(t_vm *vm, t_process *process);
int	instruction_zjmp(t_vm *vm, t_process *process);
int	instruction_ldi(t_vm *vm, t_process *process);
int	instruction_sti(t_vm *vm, t_process *process);
int	instruction_fork(t_vm *vm, t_process *process, t_process **begin);
int	instruction_lfork(t_vm *vm, t_process *process, t_process **begin);
int	instruction_aff(t_vm *vm, t_process *process);

void					free_players(t_player **first);
void 					free_vm(t_vm **vm);
void 					free_process(t_process **process);
int 					free_map(t_map *map);

void 	print_process(t_process *process);
char *take_opcode(unsigned char c, char *str);
void take_params(char *arena, int pos, int *params, char *str, int unknown);
int recup_nb_32(char *arena, int position);
int recup_nb_16(char *arena, int position);
void write_in_arena_32(t_vm *vm, int registre, int pos, int nb);
t_process	*create_process(t_process **process, t_process *tmp, int pos, int player_numero);
int				create_new_process(t_process **begin, t_process *process, int pos, int n);
void 			init_window(void);
int				inst_progress(t_process *process, int inst);
int				inst_done(t_process *process, int add_pos);

#endif
