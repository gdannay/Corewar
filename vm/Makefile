# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 16:41:29 by clegirar          #+#    #+#              #
#    Updated: 2018/05/15 18:51:40 by clegirar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	./corewar

SRCS			=	srcs/main.c			\
					srcs/header.c		\
					srcs/error.c		\
					srcs/arena.c		\
					srcs/visu.c			\
					srcs/utils.c		\
					srcs/process.c	\
					srcs/run.c			\
					srcs/instruction_1_to_5.c	\
					../op/op.c

OBJS			=	$(SRCS:.c=.o)

CC				=	@gcc

CFLAGS			=	-Wall -Werror -Wextra -I includes -I ../libft/

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
