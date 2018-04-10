/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 17:51:37 by clegirar          #+#    #+#             */
/*   Updated: 2018/01/03 16:10:51 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BUFFER 155

# include "../libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef	struct					s_parse
{
	int							plus;
	int							moins;
	int							space;
	int							zero;
	int							precision;
	int							size_field;
	int							diez;
	char						flag;
	char						*modif_len;
	char						*begin;
	char						*other;
	struct s_parse				*next;
}								t_parse;

typedef	struct					s_flags
{
	char						c;
}								t_flags;

typedef	struct					s_printf
{
	char						buff[BUFFER + 1];
	int							surplus;
	int							cursor;
	unsigned	long	long	nbl;
	long	long				nb;
}								t_printf;

typedef	struct					s_ptr_fct
{
	char						c;
	int							(*f)(va_list ap, t_parse *tmp, t_printf *ptf);
}								t_ptr_fct;

typedef	struct					s_conv
{
	char						*prefix;
	char						*arg;
	char						*new;
	char						*ret;
	char						*field;
	char						*diez;
	char						*preci;
	char						*space;
	char						*plus;
	char						*moins;
	char						c;
}								t_conv;

int								algo(va_list ap,
		t_parse *lst, t_printf *ptf);
int								c_bu(t_printf *ptf, char *str);
int								fill_count_buff(t_printf *ptf,
		char *concat, int add);
int								fill_modif_len(t_parse *new,
		char *format, int *i);
int								conv_unsigned(va_list ap,
		t_parse *tmp, t_printf *ptf);
int								conv_signed(va_list ap,
		t_parse *tmp, t_printf *ptf);
int								conv_string(va_list ap,
		t_parse *tmp, t_printf *ptf);
int								conv_char(va_list ap,
		t_parse *tmp, t_printf *ptf);
int								conv_float(va_list ap,
		t_parse *tmp, t_printf *ptf);
int								conv_mod(va_list ap,
		t_parse *tmp, t_printf *ptf);
int								conv_pointeur(va_list ap,
		t_parse *tmp, t_printf *ptf);
int								string_unicode(va_list ap,
		t_parse *tmp, t_printf *ptf);
void							conv_zero_unsigned(t_parse *tmp,
		t_printf *ptf, t_conv *conv);
void							conv_no_zero_unsigned(t_parse *tmp,
		t_printf *ptf, t_conv *conv);
void							conv_zero_signed(t_parse *tmp,
		t_printf *ptf, t_conv *conv);
void							conv_no_zero_signed(t_parse *tmp,
		t_printf *ptf, t_conv *conv);
void							fill_field_no_zero_signed(t_parse *tmp,
		t_printf *ptf, t_conv *conv);
t_parse							*create_list(char *format);
int								flag_mod(char c);
int								mng_flags(t_parse *new, char *format, int i);
int								fill_basics_struct(t_parse *new,
		char *format, int i);
int								fill_preci_field(t_parse *new,
		char *format, int *i);
void							fill_begin(t_parse *new,
		char *format, int *i);
void							fill_other(t_parse *new,
		char *format, int *i);
int								chars_modif_len(char c);
int								ft_printf(const char *format, ...);
int								ft_dprintf(int fd, const char *format, ...);
int								ft_sprintf(char *str, const char *format, ...);
int								ft_snprintf(char *str,
		size_t size, const char *format, ...);
int								ft_vprintf(const char *format, va_list ap);
int								ft_vsprintf(char *str,
		const char *format, va_list ap);
int								ft_vsnprintf(char *str, size_t size,
		const char *format, va_list ap);
void							del_list(t_parse **lst);
void							print_list(t_parse *lst);
char							*mask_unicode(unsigned int arg);

#endif
