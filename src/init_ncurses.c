/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:28:46 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/13 14:08:58 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "graphic.h"

unsigned int nisuu_id[4];

void		display_infos_border(t_vm *vm)
{
	int	i;

	i = 0;
	attron(COLOR_PAIR(BORDER));
	while (i < (64 * 3) + (2 * WIDTH_PAD) - 1)
	{
		mvprintw(0, i, "*");
		mvprintw(77, i, "*");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		mvprintw(67 + i, 0, "*");
		mvprintw(67 + i, 64 * 3 + (2 * WIDTH_PAD) - 2, "*");
		i++;
	}
	attroff(COLOR_PAIR(BORDER));
}

static void	display_border(t_vm *vm)
{
	int		i;

	i = -1;
	attron(COLOR_PAIR(BORDER));
	while (++i < (64 * 3) + (2 * WIDTH_PAD) - 2)
	{
		mvprintw(0, i, "*");
		mvprintw(64 + WIDTH_PAD, i, "*");
	}
	i = -1;
	while (++i < (64) + 2 * HEIGHT_PAD)
	{
		mvprintw(i, 0, "*");
		mvprintw(i, 64 * 3 + (2 * WIDTH_PAD) - 2, "*");
	}
	attroff(COLOR_PAIR(BORDER));
	attron(COLOR_PAIR(NEUTRAL));
	i = -1;
	while (++i < (64 * 64))
	{
		mvprintw(HEIGHT_PAD + i / 64, WIDTH_PAD + ((i % 64) * 3), "%.2hhx ",
		vm->map[i]);
	}
	attroff(COLOR_PAIR(NEUTRAL));
}

void		init_ncurses(t_vm *vm)
{
	int		i;

	i = 0;
	while (i < vm->nb_player)
	{
		vm->players_order[i] = vm->champ[i].id_player;
		++i;
	}
	initscr();
	noecho();
	curs_set(FALSE);
	start_color();
	init_pair(BORDER, GREY_COLOUR, GREY_COLOUR);
	init_pair(NEUTRAL, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	display_border(vm);
	display_infos_border(vm);
	refresh();
}
