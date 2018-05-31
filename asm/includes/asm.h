/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:39:56 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/31 11:19:00 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../op/op.h"
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../../libft/libft.h"

# define BIT_2 16711680
# define BIT_3 65280
# define T_STRING 16
# define T_INSTR 32
# define T_DIR_LAB 64
# define T_IND_LAB 128
# define T_END 256
# define T_COMMAND_NAME 512
# define T_COMMAND_COMMENT 1024
# define T_COMMENT 2048
# define ERROR 0
# define TRUE 1
# define NEXT 2
//# define malloc(x) NULL

typedef struct		s_inst
{
	char			*label;
	char			*name;
	int				code;
	char			*params[4];
	unsigned char	codage;
	struct s_inst	*next;
	struct s_inst	*prev;
}					t_inst;

t_inst				*parse_file(int fd, header_t *header, int *row);
int					check_and_save(char *line, t_inst **first, int row);
header_t			*create_header(int fd, int *row);
int					get_type(char *str);
int					check_params(t_inst *new, char *line, int row, int col);
int					find_next_char(char *str, int i);
int					find_next_space(char *str, int i);
int					convert_type(char *str);

int					fill_label(t_inst *new, char *line, int row);
int					take_label(t_inst *first);
int					verif_label(char *line, int row);
t_inst				*save_label(char *line, int next, t_inst **first);
t_inst				*initialize_inst(void);
int					add_label(t_inst *new, char *line, int i, int sauv);

int					write_in_cor(char *av, header_t *header, t_inst *first);
int					write_registre(int fd, char *param);
int					write_direct(t_inst *first, int fd, char *param);
int					write_indirect(int fd, char *param);

uint32_t			swap_32_bytes(uint32_t nb);
uint16_t			swap_16_bytes(uint16_t nb);

int					display_error(int infos, char *instr,
					char *param, char *line);
void				*exit_free(char *line, t_inst *first, header_t *header);
int					error_message(int line, int col, int type, char *str);
void				*exit_error(int row, int col, char **line, char **str);

int					check_type(header_t *header, int check, int type);
char				*check_line(char **line, int fd, int *i, int type);
int					check_length(char **str, char **line, int type, int length);
int					compute_size_program(t_inst *first, int size);

#endif
