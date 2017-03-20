/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:16:39 by jye               #+#    #+#             */
/*   Updated: 2017/03/18 18:32:54 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <graphic.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

static void	visual_print_win(t_vm *vm)
{
	unsigned int	i;
	t_champ			*win;

	win = &vm->champ[0];
	i = 0;
	while (i < vm->nb_player)
	{
		if (win->last_live < vm->champ[i].last_live)
			win = &vm->champ[i];
		++i;
	}
	mvprintw(74, 3, "winner: %s", win->name);
}

static void	npause(void)
{
	char c;

	if ((c = getch()) == 32)
	{
		while (42)
			if ((c = getch()) == 32)
				return ;
			else if (c == 27)
			{
				endwin();
				exit(EXIT_SUCCESS);
			}
	}
	else if (c == 27)
	{
		endwin();
		exit(EXIT_SUCCESS);
	}
}

void		visual_play(t_vm *vm)
{
	unsigned long	last_check;

	last_check = 0;
	timeout(1);
	while (vm->process)
	{
		npause();
		check_opt(vm);
		if (last_check == vm->cycle - vm->cycle_to_die)
		{
			checks(vm);
			purge_process(vm, last_check);
			last_check = vm->cycle;
		}
		vm->cycle += 1;
		info_curses(vm);
		refresh();
		usleep(1000);
	}
	visual_print_win(vm);
	mvprintw(75, 3, "press watever u wan u dick");
	timeout(-1);
	getch();
	endwin();
}
