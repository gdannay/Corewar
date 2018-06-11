/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegirar <clegirar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:27:26 by clegirar          #+#    #+#             */
/*   Updated: 2018/06/11 12:23:22 by clegirar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_window(void)
{
	initscr();
	noecho();
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_color(COLOR_CYAN, 214, 214, 214);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	clear();
	curs_set(FALSE);
}

void	init_window_vm(WINDOW **arena, WINDOW **infos)
{
	init_window();
	*arena = subwin(stdscr, 66, 195, 0, 0);
	*infos = subwin(stdscr, 66, 100, 0, 197);
	box(*arena, ACS_VLINE, ACS_HLINE);
	box(*infos, ACS_VLINE, ACS_HLINE);
	wrefresh(*arena);
	wrefresh(*infos);
}
