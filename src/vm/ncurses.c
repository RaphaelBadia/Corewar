/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:51:07 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/18 19:11:30 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "graphic.h"

static int	get_player_color(t_vm *vm, unsigned int id)
{
	unsigned int	i;

	i = 0;
	while (i < vm->nb_player)
	{
		if (vm->champ[i].id_player == id)
			break ;
		++i;
	}
	return (i + 1);
}

void		highlight(t_vm *vm, unsigned int pc, int len, unsigned int id)
{
	unsigned int	i;

	if (!(vm->flag & visual))
		return ;
	i = pc;
	if (id == -1U)
		id = mvinch(HEIGHT_PAD + (PTR(pc) / 64), WIDTH_PAD + ((pc % 64) * 3))
		& A_COLOR;
	else
		id = COLOR_PAIR(get_player_color(vm, id));
	while (i < pc + len)
	{
		attron(id | A_REVERSE);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3), "%.2hhx",
															vm->map[PTR(i)]);
		attroff(id | A_REVERSE);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3) + 2, " ");
		i = i + 1;
	}
}

void		unlight(t_vm *vm, unsigned int pc, int len)
{
	unsigned int	i;
	int				current_color;

	if (!(vm->flag & visual))
		return ;
	i = pc;
	while (i < pc + len)
	{
		current_color = mvinch(HEIGHT_PAD + (PTR(pc) / 64),
		WIDTH_PAD + ((pc % 64) * 3)) & A_COLOR;
		attron(current_color);
		attroff(A_REVERSE);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3), "%.2hhx",
															vm->map[PTR(i)]);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3) + 2, " ");
		i = i + 1;
	}
}

void		refresh_map(t_vm *vm, unsigned int pc, int len, unsigned int id)
{
	unsigned int	i;

	if (!(vm->flag & visual))
		return ;
	i = pc;
	id = COLOR_PAIR(get_player_color(vm, id));
	while (i < (pc + len))
	{
		attron(id);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3),
		"%.2hhx", vm->map[PTR(i)]);
		attroff(id);
		mvprintw(HEIGHT_PAD + PTR(i) / 64, WIDTH_PAD + ((i % 64) * 3) + 2, " ");
		i = i + 1;
	}
}

void		info_curses(t_vm *vm)
{
	attroff(COLOR_PAIR(1));
	attroff(COLOR_PAIR(2));
	attroff(COLOR_PAIR(3));
	attroff(COLOR_PAIR(4));
	attron(NEUTRAL);
	mvprintw(69, 3, "cycle: %lu", vm->cycle);
	mvprintw(70, 3, "%20s", "");
	mvprintw(70, 3, "nb_process: %u", vm->nb_process);
	mvprintw(71, 3, "%20s", "");
	mvprintw(71, 3, "cycle_to_die: %u", vm->cycle_to_die);
	mvprintw(72, 3, "%30s", "");
	mvprintw(72, 3, "total_live_check: %u", vm->live);
	mvprintw(73, 3, "%20s", "");
	mvprintw(73, 3, "max_checks: %u", MAX_CHECKS);
	mvprintw(74, 3, "%20s", "");
	attroff(NEUTRAL);
}
