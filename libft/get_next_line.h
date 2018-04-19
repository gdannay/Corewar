/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:30:42 by gdannay           #+#    #+#             */
/*   Updated: 2018/04/19 14:13:14 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"
# include <fcntl.h>
# include <string.h>
# define BUFF_SIZE 2048

typedef struct		s_lst
{
	int				fd;
	char			*txt;
	struct s_lst	*next;
}					t_lst;

int					get_next_line(const int fd, char **line);
#endif
