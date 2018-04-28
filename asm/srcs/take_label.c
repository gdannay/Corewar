/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_label.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 15:11:01 by vferreir          #+#    #+#             */
/*   Updated: 2018/04/28 16:45:22 by vferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int add_position_bottom(t_inst *list)
{
	int i;
	int pos;

	pos = 1;
	if (list->code == 1)
		return (5);
	if (list->code != 12 && list->code != 9 && list->code != 15)
		pos++;
	i = -1;
	while (list->params[++i])
	{
		if (list->params[i][0] == 'r')
			pos++;
		else if (list->params[i][0] == DIRECT_CHAR)
			pos += 4;
		else
			pos += 2;
	}
	return (pos);
}

static int search_on_bottom(t_inst *list, char *str)
{
	int pos;

	pos = 0;
	str = ft_strstr(str, ":") + 1;
	if (list->label && ft_strcmp(list->label, str) == 0)
		return (0);
	while (list)
	{
		if (list->label && ft_strcmp(list->label, str) == 0)
			return (pos);
		list = list->next;
		if (list)
			pos += add_position_bottom(list);
	}
	return (-1);
}

static int search_on_top(t_inst *list, char *str)
{
	str = ft_strstr(str, ":") + 1;
	while (list)
	{
		if (list->label)
		{
			if (ft_strcmp(list->label, str) == 0)
				return (TRUE);
		}
		list = list->prev;
	}
	return (ERROR);
}

static void change_params(char **str, int pos)
{
	char *direct;

	if (*str[0] == DIRECT_CHAR)
	{
		ft_strdel(str);
		direct = malloc(sizeof(char) * 2);
		direct[0] = DIRECT_CHAR;
		direct[1] = '\0';
		*str = ft_strjoindel(direct, ft_itoa(pos));
	}
	else
	{
		ft_strdel(str);
		*str = ft_itoa(pos);
	}
}

int take_label(t_inst *list)
{
	int i;
	int pos;

	while (list)
	{
		i = -1;
		while (list->params[++i])
		{
			if (list->params[i][0] == LABEL_CHAR || list->params[i][1] == LABEL_CHAR)
			{
				if ((pos = search_on_bottom(list, list->params[i])) != -1)
					change_params(&list->params[i], pos);
				else if (search_on_top(list, list->params[i]) != ERROR)
				{

				}
				else
				{
					ft_printf("No such label %s\n", ft_strstr(list->params[i], ":") + 1);
					return (ERROR);
				}
			}
		}
		list = list->next;
	}
	return (TRUE);
}
