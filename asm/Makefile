# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegirar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/10 16:41:29 by clegirar          #+#    #+#              #
#    Updated: 2018/04/17 15:17:57 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	asm

SRCS			=	srcs/main.c			\
					srcs/parsing.c		\
					srcs/list.c			\
					srcs/header.c

OBJS			=	$(SRCS:.c=.o)

CC				=	gcc

CFLAGS			=	-Wall -Werror -Wextra -I includes -I ../libft/

LFLAGS			=	../libft/libft.a

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					make -C ../libft
					$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

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
