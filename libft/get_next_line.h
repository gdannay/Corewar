/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:44:46 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/02 11:10:38 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# define BUFF_SIZE 10000
# define CHAR '\n'

typedef	struct		s_gnl
{
	int				fd;
	char			*tmp;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(const int fd, char **line);

#endif
