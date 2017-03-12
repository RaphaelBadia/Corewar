/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:51:07 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/12 17:56:04 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "graphic.h"

void	highlight(t_vm *vm, unsigned int pc, int len, unsigned int id)
{
	int				it;
	unsigned int	i;

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
	unsigned int		i;
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

void	refresh_map(t_vm *vm, unsigned int pc, int len, unsigned int id)
{
	int		it;
	unsigned int		i;

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
