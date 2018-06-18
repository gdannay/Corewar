# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/11 10:50:26 by clegirar          #+#    #+#              #
#    Updated: 2018/06/18 14:14:30 by clegirar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM				= asm
NAME			= corewar

CC				= gcc
CFLAGS		= -Wall -Werror -Wextra

ASM_SRCS		=	asm_srcs/main.c			\
					asm_srcs/parsing.c		\
					asm_srcs/label.c		\
					asm_srcs/parameters.c	\
					asm_srcs/dereference.c	\
					asm_srcs/header.c		\
					asm_srcs/check_header.c	\
					asm_srcs/exit_error.c	\
					asm_srcs/write.c		\
					asm_srcs/write_type.c	\
					asm_srcs/instructions.c	\
					op/op.c			\
					asm_srcs/type.c

COREWAR_SRCS	=	vm_srcs/main.c			\
					vm_srcs/read_av.c		\
					vm_srcs/create_player.c	\
					vm_srcs/error.c		\
					vm_srcs/create_vm.c		\
					vm_srcs/visu.c			\
					vm_srcs/utils.c		\
					vm_srcs/initialize_process.c	\
					vm_srcs/run.c			\
					vm_srcs/aritmetical_instructions.c	\
					vm_srcs/logical_instructions.c	\
					vm_srcs/direct_instructions.c		\
					vm_srcs/indirect_instructions.c	\
					vm_srcs/fork_rest_instructions.c	\
					vm_srcs/inst_done_progress.c	\
					vm_srcs/take_opcode_params.c	\
					vm_srcs/free_all.c	\
					vm_srcs/init_visu.c	\
					vm_srcs/print_entry_result.c	\
					vm_srcs/fct_dump.c	\
					op/op.c

LIBFT					= libft/libft.a
LIB_DIR				=	libft
HEADER_DIR		= includes
ASM_OBJS			= $(ASM_SRCS:.c=.o)
COREWAR_OBJS	= $(COREWAR_SRCS:.c=.o)
GREEN					=	\x1b[32m
END						=	\x1b[0m

all:  lib $(ASM) $(NAME)

$(ASM): $(LIBFT) $(ASM_OBJS)
			@$(CC) $(CFLAGS) -o $(ASM) $(ASM_OBJS) -L $(LIB_DIR) -lft -I $(HEADER_DIR)
			@echo "$(ASM): $(GREEN)Done$(END)"

$(NAME): $(LIBFT) $(COREWAR_OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(COREWAR_OBJS) -L $(LIB_DIR) -lft -lncurses -I $(HEADER_DIR)
			@echo "$(NAME): $(GREEN)Done$(END)"

lib:
			@make -C $(LIB_DIR)

%.o : %.c
			@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER_DIR)

clean:
			@make clean -C $(LIB_DIR)
			@rm -rf $(ASM_OBJS)
			@rm -rf $(COREWAR_OBJS)
			@echo "$(ASM) clean : $(GREEN)Done$(END)"
			@echo "$(NAME) clean : $(GREEN)Done$(END)"

fclean:
			@make fclean -C $(LIB_DIR)
			@rm -rf $(ASM_OBJS)
			@rm -rf $(COREWAR_OBJS)
			@rm -rf $(ASM)
			@rm -rf $(NAME)
			@echo "$(ASM) fclean : $(GREEN)Done$(END)"
			@echo "$(NAME) fclean : $(GREEN)Done$(END)"

re: fclean all

.PHONY: all clean fclean re
