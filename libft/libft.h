/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 08:52:16 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/09 16:47:04 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define ABS(Value) ((Value) < 0 ? - (Value) : (Value))

# include "Printf/includes/ft_printf.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef	struct					s_list
{
	void						*content;
	size_t						content_size;
	struct s_list				*next;
}								t_list;

int								ft_iterative_power(int nb, int power);
int								ft_intlen(int *str);
int								ft_tablen_int(int **tab);
int								ft_tablen(char **tab);
char							**ft_tabdup(char **tab);
size_t							ft_strlcat(char *dst,
		const char *src, size_t size);
int								ft_atoi(const char *str);
void							ft_bzero(void *s, size_t n);
int								ft_isalnum(int c);
int								ft_isalpha(int c);
int								ft_isascii(int c);
int								ft_isdigit(int c);
int								ft_isprint(int c);
void							*ft_memccpy(void *dest,
		const void *src, int c, size_t n);
void							*ft_memchr(const void *s, int c,
		size_t n);
int								ft_memcmp(const void *s1,
		const void *s2, size_t n);
void							*ft_memcpy(void *dest,
		const void *src, size_t n);
void							*ft_memmove(void *dest,
		const void *src, size_t n);
void							*ft_memset(void *s, int c, size_t n);
char							*ft_strcat(char *dest, const char *src);
char							*ft_strchr(const char *s, int c);
int								ft_strcmp(const char *s1, const char *s2);
char							*ft_strcpy(char *dest, const char *src);
char							*ft_strdup(const char *s);
size_t							ft_strlen(char const *str);
char							*ft_strncat(char *dest,
		const char *src, size_t n);
int								ft_strncmp(const char *s1,
		const char *s2, size_t n);
char							*ft_strncpy(char *dest,
		const char *src, size_t n);
char							*ft_strnstr(const char *str,
					const char *to_find, size_t len);
char							*ft_strrchr(const char *s, int c);
char							*ft_strstr(const char *str,
		const char *to_find);
int								ft_tolower(int c);
int								ft_strchar(char *s, char c);
int								ft_toupper(int c);
char							*ft_lltoa(unsigned long long n);
char							*ft_itoa(int n);
void							*ft_memalloc(size_t size);
void							ft_memdel(void **ap);
void							ft_putchar(char c);
void							ft_putchar_fd(char c, int fd);
void							ft_putendl(char const *s);
void							ft_putendl_fd(char const *s, int fd);
void							ft_putnbr(int n);
void							ft_putnbr_fd(int n, int fd);
void							ft_putstr(char const *s);
void							ft_putstr_fd(char const *s, int fd);
void							ft_strclr(char *s);
void							ft_strdel(char **as);
int								ft_strequ(char const *s1,
		char const *s2);
void							ft_striter(char *s,
		void (*f)(char*));
void							ft_striteri(char *s,
		void (*f)(unsigned int, char*));
char							*ft_strjoin(char const *s1,
		char const *s2);
char							*ft_strnjoin(char const *s1,
		char const *s2, size_t n);
char							*ft_strmap(char const *s,
		char (*f)(char));
char							*ft_strmapi(char const *s,
		char (*f)(unsigned int, char));
int								ft_strnequ(char const *s1,
		char const *s2, size_t n);
void							*ft_memalloc(size_t n);
char							*ft_strnew(size_t size);
char							**ft_strsplit(char const *s, char c);
char							*ft_strsub(char const *s,
		unsigned int start, size_t len);
char							*ft_strtrim(char *s);
void							ft_lstadd(t_list **alst, t_list *new);
void							ft_lstdel(t_list **alst,
		void (*del)(void*, size_t));
void							ft_lstdelone(t_list **alst,
		void (*del)(void*, size_t));
void							ft_lstiter(t_list *lst,
		void (*f)(t_list *elem));
t_list							*ft_lstmap(t_list *lst,
		t_list *(*f)(t_list *elem));
t_list							*ft_lstnew(void const *content,
		size_t content_size);
t_list							*ft_lstparams(int ac, char **av);
int								ft_lstlen(t_list *alst);
void							ft_puttab(char **tab, int endl);
char							*ft_epurstr(char *str);
void							ft_swap(int *a, int *b);
char							*ft_strcapitalize(char *str);
char							*ft_strrev(char *str);
void							*ft_memrealloc(void *s,
		size_t size_o, size_t size_n);
void							ft_tabdel(char ***tab);
void							ft_tabdel_int(int ***tab);
void							ft_puttab_int(int **tab);
void							ft_putint(int *tab);
char							*ft_lltoa_base(unsigned long long nb,
		int base, char c);
char							*ft_itoa_base(unsigned int nb,
		int base, char c);
char							*ft_len_dup(int n, char c);
char							*ft_strndup(char const *s, int n);
unsigned	long	long		ft_atol(const char *str);
unsigned	long	long		ft_atoll_base(char *arg,
		int base, char c);
char							*ft_lltoa_signed(long long n);
long	long					ft_atol_signed(const char *str);
unsigned	int					ft_atoi_base(char *str,
		int base, char c);
char							**ft_tabcpy(char **tab, int i);
char							**ft_splitspace(char const *s);
int								ft_stridx(char *str, char *cmp);
int								ft_string_isdigit(char *str);
char							*ft_strjoindel(char const *s1, char const *s2);
int								ft_countchr(char *str, char c);

#endif
