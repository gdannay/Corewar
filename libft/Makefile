# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 08:52:25 by clegirar          #+#    #+#              #
#    Updated: 2018/05/21 14:07:40 by gdannay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_atoi.c				\
			ft_strchar.c			\
			ft_atol.c				\
			ft_atoi_base.c			\
			ft_atol_signed.c		\
			ft_iterative_power.c	\
			ft_bzero.c				\
			ft_isalnum.c			\
			ft_isalpha.c			\
			ft_strlcat.c			\
			ft_isascii.c			\
			ft_isdigit.c			\
			ft_isprint.c			\
			ft_memccpy.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_memcpy.c				\
			ft_memmove.c			\
			ft_memset.c				\
			ft_strcat.c				\
			ft_strchr.c				\
			ft_strcmp.c				\
			ft_strcpy.c				\
			ft_strdup.c				\
			ft_strlen.c				\
			ft_strncat.c			\
			ft_strncmp.c			\
			ft_strncpy.c			\
			ft_strnstr.c			\
			ft_strrchr.c			\
			ft_strstr.c				\
			ft_tolower.c			\
			ft_toupper.c			\
			ft_itoa.c				\
			ft_lltoa.c				\
			ft_lltoa_signed.c		\
			ft_memalloc.c			\
			ft_memdel.c				\
			ft_putchar.c			\
			ft_putchar_fd.c			\
			ft_putendl.c			\
			ft_putendl_fd.c			\
			ft_putnbr.c				\
			ft_putnbr_fd.c			\
			ft_putstr.c				\
			ft_putstr_fd.c			\
			ft_strclr.c				\
			ft_strdel.c				\
			ft_strequ.c				\
			ft_striter.c			\
			ft_striteri.c			\
			ft_strjoin.c			\
			ft_strnjoin.c			\
			ft_strjoindel.c		\
			ft_strmap.c				\
			ft_strmapi.c			\
			ft_strnequ.c			\
			ft_strnew.c				\
			ft_strsplit.c			\
			ft_strsub.c				\
			ft_strtrim.c			\
			ft_lstadd.c				\
			ft_lstdel.c				\
			ft_lstdelone.c			\
			ft_lstiter.c			\
			ft_lstmap.c				\
			ft_lstnew.c				\
			ft_lstlen.c				\
			ft_lstparams.c			\
			ft_puttab.c				\
			ft_epurstr.c			\
			ft_swap.c				\
			ft_strcapitalize.c		\
			ft_strrev.c				\
			ft_memrealloc.c			\
			get_next_line.c			\
			ft_tabdel.c				\
			ft_tabdup.c				\
			ft_tablen.c				\
			ft_puttab_int.c			\
			ft_tablen_int.c			\
			ft_intlen.c				\
			ft_putint.c				\
			ft_tabdel_int.c			\
			ft_itoa_base.c			\
			ft_lltoa_base.c			\
			ft_len_dup.c			\
			ft_strndup.c			\
			ft_atoll_base.c			\
			ft_tabcpy.c				\
			ft_splitspace.c			\
			ft_stridx.c				\
			ft_string_isdigit.c \
			./Printf/srcs/ft_printf.c					\
			./Printf/srcs/ft_dprintf.c					\
			./Printf/srcs/ft_sprintf.c					\
			./Printf/srcs/ft_vprintf.c					\
			./Printf/srcs/create_list.c				\
			./Printf/srcs/fill_list.c					\
			./Printf/srcs/manage_list.c				\
			./Printf/srcs/algo.c						\
			./Printf/srcs/conv_char.c					\
			./Printf/srcs/conv_float.c					\
			./Printf/srcs/conv_mod.c					\
			./Printf/srcs/conv_signed.c				\
			./Printf/srcs/conv_string.c				\
			./Printf/srcs/conv_unsigned.c				\
			./Printf/srcs/conv_pointeur.c				\
			./Printf/srcs/check_mng_buff.c				\
			./Printf/srcs/mask_unicode.c				\
			./Printf/srcs/conv_string_unicode.c		\
			./Printf/srcs/manage_flags.c				\
			./Printf/srcs/fill_list_len.c				\
			./Printf/srcs/zero_unsigned.c				\
			./Printf/srcs/no_zero_unsigned.c			\
			./Printf/srcs/zero_signed.c				\
			./Printf/srcs/no_zero_signed.c				\
			./Printf/srcs/fill_field_no_zero_signed.c

CC		=	gcc

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -I./ -I./Printf/includes

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

%.o		: 	%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean	:
	rm -rf $(OBJS)

fclean	:
	rm -rf $(OBJS)
	rm -rf $(NAME)

re		:	fclean all

.PHONY	:	all %.o clean fclean re
