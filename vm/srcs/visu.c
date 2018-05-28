/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:49:42 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/28 14:23:48 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 		init_window(void)
{
	initscr();
	noecho();
	curs_set(FALSE);
}

void 		print_arena(WINDOW *visu, t_vm *vm, char *arena)
{
	int	i;
	int	x;
	int	y;

	(void)visu;
	(void)arena;
	(void)vm;
	i = 0;
	x = 2;
	y = 1;
	while (i < MEM_SIZE)
	{
		/*init_color(COLOR_RED, 700, 0, 0);
		  attron(COLOR_PAIR(1));*/
		mvwprintw(visu, y, x, "%02hhx", arena[i]);
		wrefresh(visu);
		//attroff(COLOR_PAIR(1));
		i++;
		if (i != 0 && i % 64 == 0)
		{
			x = 2;
			y += 1;
		}
		else
			x += 3;
	}
}
