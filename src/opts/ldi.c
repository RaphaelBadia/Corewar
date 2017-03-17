/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:43:13 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/13 15:52:56 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include "vm.h"

void	ldi(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	int				i;
	int				r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	i = 0;
	octal[0] = vm->map[PTR(pc[0] + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	while (i < 2)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i], 1, 1});
		++i;
	}
	r[2] = vm->map[PTR(pc[1])];
	if (vm->flag & verbose)
		printf("P %4d | ldi %d %d r%d\n", process->id, r[0], r[1], r[2]);
	process->r[r[2] - 1] = get_dir(vm, pc[0] + ((r[0] + r[1]) % IDX_MOD), 0);
	process->pc = pc[1] + 1;
}
