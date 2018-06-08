/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <gdannay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:07:18 by gdannay           #+#    #+#             */
/*   Updated: 2018/06/08 18:15:10 by clegirar         ###   ########.fr       */
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
# define D_FLAG 1
# define N_FLAG 2
# define V_FLAG 4
# define A_FLAG 8

typedef struct			s_process
{
	int					registre[REG_NUMBER];
	int					color;
	int					position;
	int					live;
	char				carry;
	int					cycle;
	char				inst;
	struct s_process	*next;
	struct s_process	*prev;
}						t_process;

typedef struct			s_player
{
	header_t			*header;
	char				*code;
	int					numero;
	int					global_live;
	int					last_live;
	int					start;
	int					color;
	struct s_player		*next;
	struct s_player		*prev;
}						t_player;

typedef struct			s_vm
{
	WINDOW				*arena_w;
	WINDOW				*infos;
	char				*arena;
	char				*arena_player;
	unsigned long long	cycle;
	int					cycle_to_die;
	int					cycle_delta;
	int					nbr_live;
	int					max_checks;
	unsigned long		process;
	int					nbr_players;
	int					ecart;
}						t_vm;

typedef	struct			s_map
{
	struct s_player		*player;
	char				flag;
	int					dump;
	struct s_vm			*vm;
	struct s_process	*process;
	int					space;
}						t_map;

typedef	struct			s_ptr
{
	int					current;
	int					(*f)(t_vm *vm, t_process *process);
}						t_ptr;

uint32_t				swap_32_bytes(uint32_t nb);
void					*header_error(header_t *header, char *str, char *name);
int						code_error(char *buff, t_player **player,
		char *str, char *name);
void					*error_read_av(char *format, char *param);
char					*create_arena(t_player *first);
void					print_arena(WINDOW *visu, t_vm *vm,
		char *arena, t_map *map);
void					print_infos(WINDOW *infos, t_map *map);
t_player				*read_av(char **av, int ac, int i);
int						recup_int(char *str);
t_vm					*create_vm(t_player *first);
t_process				*initialize_process(t_map *map);
int						run_vm(t_map *map, int ret, int get);
void					display_windows_vm(WINDOW *arena, WINDOW *infos,
		t_map *map, int *get);
t_player				*create_player(t_player **first,
		header_t *header, int pl_nbr);

int						instruction_live(t_vm *vm, t_process *process,
		t_player *player);
int						instruction_ld(t_vm *vm, t_process *process);
int						instruction_lld(t_vm *vm, t_process *process);
int						instruction_lldi(t_vm *vm, t_process *process);
int						instruction_st(t_vm *vm, t_process *process);
int						instruction_add(t_vm *vm, t_process *process);
int						instruction_sub(t_vm *vm, t_process *process);
int						instruction_and(t_vm *vm, t_process *process);
int						instruction_or(t_vm *vm, t_process *process);
int						instruction_xor(t_vm *vm, t_process *process);
int						instruction_zjmp(t_vm *vm, t_process *process);
int						instruction_ldi(t_vm *vm, t_process *process);
int						instruction_sti(t_vm *vm, t_process *process);
int						instruction_fork(t_vm *vm, t_process *process,
		t_process **begin);
int						instruction_lfork(t_vm *vm, t_process *process,
		t_process **begin);
int						instruction_aff(t_vm *vm, t_process *process);

void					free_players(t_player **first);
void					free_vm(t_vm **vm);
void					free_process(t_process **process);
int						free_map(t_map *map);

void					init_window_vm(WINDOW **arena, WINDOW **infos);
void					print_process(t_process *process);
int						take_opcode(unsigned char c, char *str);
void					take_params(char *arena, int pos,
		int *params, char *str);
int						recup_nb_32(char *arena, int position);
int						recup_nb_16(char *arena, int position);
void					write_in_arena_32(t_vm *vm, int registre,
		int pos, int nb);
int						create_new_process(t_process **begin,
		t_process *process, int pos, int n);
void					init_window(void);
int						inst_progress(t_process *process, int inst);
int						inst_done(t_process *process, int add_pos);

void					print_params(int *params);

#endif
