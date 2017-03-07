#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "vm.h"


# define HEIGHT_PAD 2
# define WIDTH_PAD 3
# define BORDER 5
# define NEUTRAL 6

void	init_ncurses(t_vm *vm);
void	refresh_map(t_vm *vm, unsigned int pc, int len, unsigned int color);
void	highlight(t_vm *vm, unsigned int pc, int len, unsigned int id);
void	unlight(t_vm *vm, unsigned int pc, int len);

static	unsigned int nisuu_id[4];
#endif
