# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegirar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 16:41:29 by clegirar          #+#    #+#              #
#    Updated: 2018/05/17 15:16:27 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	asm

SRCS			=	srcs/main.c			\
					srcs/parsing.c		\
					srcs/label.c		\
					srcs/parameters.c	\
					srcs/dereference.c	\
					srcs/header.c		\
					srcs/exit_error.c	\
					srcs/write.c		\
					srcs/instructions.c	\
					../op/op.c			\
					srcs/type.c

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -I includes -I ../libft/

LFLAGS			=	../libft/libft.a -g3 -fsanitize=address

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					@make -C ../libft
					@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)
					@rm -rf $(OBJS)

%.o				:	%.c
					@$(CC) -o $@ -c $< $(CFLAGS)

clean			:
					@make clean -C ../libft
					@rm -rf $(OBJS)

fclean			:
					@rm -rf $(OBJS)
					@make fclean -C ../libft
					@rm -rf $(NAME)

re				:	fclean all
