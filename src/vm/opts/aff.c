/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:46:02 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/20 18:05:21 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "vm.h"

void			aff(t_vm *vm, t_process *process)
{
	int		r;
	int		pc;

	pc = process->pc;
	r = vm->map[PTR(pc + 2)];
	r = process->r[r - 1] % 256;
	if (vm->flag & aff_flag)
		write(r, &r, 1);
	process->pc += 3;
}
