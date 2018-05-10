/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 10:49:42 by clegirar          #+#    #+#             */
/*   Updated: 2018/05/10 15:09:25 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 		visu(char *arena, t_player *first)
{
	int	i;
	int	x;
	int	y;

	initscr();
	(void)first;
	noecho();
	/*start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);*/
	curs_set(FALSE);

	while (1)
	{
		//clear();
		i = 0;
		x = 0;
		y = 0;
		while (i < MEM_SIZE)
		{
			/*init_color(COLOR_RED, 700, 0, 0);
			attron(COLOR_PAIR(1));*/
			mvprintw(y, x, "%02hhx", arena[i]);
			refresh();
			//attroff(COLOR_PAIR(1));
			i++;
			if (i != 0 && i % 64 == 0)
			{
				x = 0;
				y += 1;
			}
			else
				x += 3;
		}
	}
	endwin();
}
