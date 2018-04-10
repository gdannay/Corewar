/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:47:00 by clegirar          #+#    #+#             */
/*   Updated: 2017/12/03 15:58:44 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static	t_gnl	*find_maillon(t_gnl *lst, const int fd)
{
	t_gnl	*tmp;
	t_gnl	*new;

	if (lst == NULL)
	{
		if (!(lst = (t_gnl *)ft_memalloc(sizeof(t_gnl))))
			return (NULL);
		lst->fd = fd;
		lst->tmp = NULL;
		lst->next = NULL;
		return (lst);
	}
	new = lst;
	while (new && new->fd != fd)
	{
		tmp = new;
		new = new->next;
	}
	if (new == NULL)
	{
		new = find_maillon(new, fd);
		tmp->next = new;
	}
	return (new);
}

static	void	del_lst(t_gnl *temp, t_gnl **lst)
{
	t_gnl	*new;
	t_gnl	*tmp;

	new = *lst;
	tmp = *lst;
	if (new == temp)
		*lst = temp->next;
	while (new && new != temp)
	{
		tmp = new;
		new = new->next;
	}
	if (new == temp)
		tmp->next = temp->next;
	free(temp->tmp);
	free(temp);
}

static	int		check_char(t_gnl *temp, char **line, t_gnl **lst)
{
	char	*l;

	if (ft_strchr(temp->tmp, CHAR))
	{
		*line = ft_strsub(temp->tmp, 0, ft_strchr(temp->tmp, CHAR) - temp->tmp);
		l = temp->tmp;
		temp->tmp = ft_strsub(temp->tmp, ft_strchr(temp->tmp, CHAR)
				- temp->tmp + 1, ft_strlen(ft_strchr(temp->tmp, CHAR)));
		ft_strdel(&l);
		return (1);
	}
	else if (ft_strlen(temp->tmp) > 0 && temp->tmp[0] != '\0'
			&& ft_strchr(temp->tmp, '\0'))
	{
		*line = ft_strdup(temp->tmp);
		ft_strdel(&temp->tmp);
		return (1);
	}
	del_lst(temp, lst);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static	t_gnl	*lst = NULL;
	t_gnl			*temp;
	char			buff[BUFF_SIZE + 1];
	int				ret;

	if (line == NULL || fd < 0)
		return (-1);
	if (lst == NULL)
		lst = find_maillon(lst, (int)fd);
	temp = find_maillon(lst, (int)fd);
	ft_bzero(buff, BUFF_SIZE + 1);
	ret = 0;
	while (ft_strchr(temp->tmp, CHAR) == NULL
			&& (ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		temp->tmp = ft_memrealloc(temp->tmp,
				ft_strlen(temp->tmp), ft_strlen(temp->tmp) + BUFF_SIZE + 1);
		temp->tmp = ft_strcat(temp->tmp, buff);
		ft_bzero(buff, BUFF_SIZE + 1);
	}
	if (ret == -1)
		return (-1);
	return (check_char(temp, line, &lst));
}
