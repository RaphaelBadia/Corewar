/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 17:31:05 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/13 14:09:08 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H
# include "vm.h"

# define HEIGHT_PAD 2
# define WIDTH_PAD 3
# define BORDER 5
# define NEUTRAL 6
# define GREY_COLOUR 246

void	init_ncurses(t_vm *vm);
void	refresh_map(t_vm *vm, unsigned int pc, int len, unsigned int color);
void	highlight(t_vm *vm, unsigned int pc, int len, unsigned int id);
void	unlight(t_vm *vm, unsigned int pc, int len);
void	info_curses(t_vm *vm);

#endif
