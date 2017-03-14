/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:45:43 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/13 15:53:29 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
#include "vm.h"

void	lfork(t_vm *vm, t_process *process)
{
	t_process		*new_p;
	unsigned int	pc;
	int				bool_;
	short			target;
	unsigned char	byte_code;

	if (!(new_p = malloc(sizeof(t_process))))
		p_error();
	pc = process->pc;
	target = (short)get_dir(vm, pc + 1, 1);
	memcpy(new_p, process, sizeof(t_process));
	new_p->pc += (target);
	byte_code = vm->map[PTR(new_p->pc)];
	vm->nb_process += 1;
	if (vm->flag & verbose)
		printf("P %4d | lfork %hd (%d)\n", process->id, target, target);
	bool_ = (byte_code > 0 && byte_code <= 16);
	new_p->op_code = bool_ ? byte_code : 0;
	new_p->exec_cycle = bool_ ? g_op_tab[byte_code].cycles + vm->cycle : 0;
	new_p->id = vm->id_track++;
	push_lst__(&vm->process, new_p);
	process->pc += 3;
}
