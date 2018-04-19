/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:39:56 by clegirar          #+#    #+#             */
/*   Updated: 2018/04/17 18:29:39 by gdannay          ###   ########.fr       */
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
# define ERROR 0

typedef struct		s_inst
{
	char			*label;
	char			*name;
	int				p1;
	int				p2;
	int				p3;
	struct s_inst	*next;
	struct s_inst	*prev;
}					t_inst;

t_inst				*parse_file(int fd);
void				free_list(t_inst *first);
void				*exit_free(char *line, t_inst *first, header_t *header, char **split);
header_t			*create_header(int fd);
void				error_message(int line, int col, int type, char *str);
int					get_type(char *str);
int					get_index(char *str);

#endif
