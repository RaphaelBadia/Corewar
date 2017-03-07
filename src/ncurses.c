/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:11:42 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/07 22:09:20 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "vm.h"
#include "graphic.h"

void	init_ncurses(t_vm *vm)
{
	int	i;

	i = 0;
	initscr();
	noecho();
	curs_set(FALSE);
	start_color();
	init_pair(BORDER, 246, 246);// gris tmtc
	init_pair(NEUTRAL, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	while (i < vm->nb_player)
	{
		nisuu_id[i] = vm->champ[i].id_player;
		++i;
	}
	i = 0;
	attron(COLOR_PAIR(BORDER));
	while (i < (64 * 3) + (2 * WIDTH_PAD) - 2)
	{
		mvprintw(0, i, "*");
		mvprintw(64 + WIDTH_PAD, i, "*");
		i++;
	}
	i = 0;
	while (i < (64) + 2 * HEIGHT_PAD)
	{
		mvprintw(i, 0, "*");
		mvprintw(i, 64 * 3 + (2 * WIDTH_PAD) - 2, "*");
		i++;
	}
	attroff(COLOR_PAIR(BORDER));
	attron(COLOR_PAIR(NEUTRAL));
	i = 0;
	while (i < (64 * 64))
	{
		mvprintw(HEIGHT_PAD + i / 64, WIDTH_PAD + ((i % 64) * 3), "%.2hhx ", vm->map[i]);
		i++;
	}
	attroff(COLOR_PAIR(NEUTRAL));
	refresh();
	sleep(1);
}

void	refresh_map(t_vm *vm, unsigned int pc, int len, unsigned int id)
{
	int		it;
	int		i;

	i = pc;
	it = 0;
	while (it < vm->nb_player)
	{
		if (nisuu_id[it] == id)
		{
			break ;
		}
		++it;
	}
	id = COLOR_PAIR(it + 1);
	while (i < (pc + len))
	{
		attron(id);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3), "%.2hhx", vm->map[PTR(i)]);
		attroff(id);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3) + 2, " ");
		i = i + 1;
	}
}

void	highlight(t_vm *vm, unsigned int pc, int len, unsigned int id)
{
	int		it;
	int		i;

	// i = 4095
	i = pc;
	it = 0;
	while (it < vm->nb_player)
	{
		if (nisuu_id[it] == id)
		{
			break ;
		}
		++it;
	}
	if (id == -1)
		id = mvinch(HEIGHT_PAD + (PTR(pc) / 64), WIDTH_PAD + ((pc % 64) * 3)) & A_COLOR;
	else
		id = COLOR_PAIR(it + 1);
	while (i < pc + len)
	{
		attron(id | A_REVERSE);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3), "%.2hhx", vm->map[PTR(i)]);
		attroff(id | A_REVERSE);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3) + 2, " ");
		i = i + 1;
	}
}

void	unlight(t_vm *vm, unsigned int pc, int len)
{
	int		i;
	int		current_color;

	i = pc;
	while (i < pc + len)
	{
		current_color = mvinch(HEIGHT_PAD + (PTR(pc) / 64), WIDTH_PAD + ((pc % 64) * 3)) & A_COLOR;
		attron(current_color);
		attroff(A_REVERSE);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3), "%.2hhx", vm->map[PTR(i)]);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3) + 2, " ");
		i = i + 1;
	}
}
