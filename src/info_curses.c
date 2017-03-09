/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_curses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 22:19:16 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/09 18:02:26 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ncurses.h>
// #include "vm.h"
// #include "graphic.h"
//
// void		hardcoded_shit(t_vm *vm)
// {
// 	int	i;
//
// 	i = 0;
// 	attron(COLOR_PAIR(BORDER));
// 	while (i < (64 * 3) + (2 * WIDTH_PAD) - 1)
// 	{
// 		mvprintw(0, i, "*");
// 		mvprintw(77, i, "*");
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 10)
// 	{
// 		mvprintw(67 + i, 0, "*");
// 		mvprintw(67 + i, 64 * 3 + (2 * WIDTH_PAD) - 2, "*");
// 		i++;
// 	}
// 	attroff(COLOR_PAIR(BORDER));
// }
//
// void	info_curses(t_vm *vm)
// {
// 	attron(NEUTRAL);
// 	mvprintw(69, 3, "cycle: %lu", vm->cycle);
// 	mvprintw(70, 3, "%20s", "");
// 	mvprintw(70, 3, "nb_process: %u", vm->nb_process);
// 	mvprintw(71, 3, "%20s", "");
// 	mvprintw(71, 3, "cycle_to_die: %u", vm->cycle_to_die);
// 	mvprintw(72, 3, "%30s", "");
// 	mvprintw(72, 3, "total_live_check: %u", vm->live);
// 	mvprintw(73, 3, "%20s", "");
// 	mvprintw(73, 3, "max_checks: %u", MAX_CHECKS);
// 	mvprintw(74, 3, "%20s", "");
// 	mvprintw(74, 3, "winner: ");
// 	attroff(NEUTRAL);
// }
