# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 16:41:29 by clegirar          #+#    #+#              #
#    Updated: 2018/06/08 16:27:14 by clegirar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	./corewar

SRCS			=	srcs/main.c			\
					srcs/read_av.c		\
					srcs/create_player.c	\
					srcs/error.c		\
					srcs/create_vm.c		\
					srcs/visu.c			\
					srcs/utils.c		\
					srcs/initialize_process.c	\
					srcs/run.c			\
					srcs/instruction_1_to_5.c	\
					srcs/instruction_6_to_10.c	\
					srcs/instruction_11_to_15.c	\
					srcs/instruction_16.c	\
					srcs/utils_instructions.c	\
					srcs/free_all.c	\
					srcs/init_visu.c	\
					../op/op.c

OBJS			=	$(SRCS:.c=.o)

CC				=	@gcc

CFLAGS			=	 -I includes -I ../libft/

LFLAGS			=	../libft/libft.a -lncurses -g3 -fsanitize=address

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					@make -C ../libft
					@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)
					@rm -rf $(OBJS)

%.o				:	%.c
					$(CC) -o $@ -c $< $(CFLAGS)

clean			:
					make clean -C ../libft
					rm -rf $(OBJS)

fclean			:
					rm -rf $(OBJS)
					make fclean -C ../libft
					rm -rf $(NAME)

re				:	fclean all
