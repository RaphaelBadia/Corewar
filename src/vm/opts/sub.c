/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:41:46 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/13 15:49:23 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <vm.h>

void	sub(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	int				r[3];

	pc = process->pc;
	r[0] = vm->map[PTR(pc + 2)];
	r[1] = vm->map[PTR(pc + 3)];
	r[2] = vm->map[PTR(pc + 4)];
	if (vm->flag & verbose)
		ft_printf("P %4d | sub r%d r%d r%d\n", process->id, r[0], r[1], r[2]);
	r[0] = process->r[r[0] - 1];
	r[1] = process->r[r[1] - 1];
	if ((process->r[r[2] - 1] = r[0] - r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += 5;
}
