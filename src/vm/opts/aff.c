/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:46:02 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/23 15:09:48 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <ft_printf.h>

void			aff(t_vm *vm, t_process *process)
{
	int		r;
	int		pc;

	pc = process->pc;
	r = vm->map[PTR(pc + 2)];
	r = process->r[r - 1] % 256;
	if (vm->flag & aff_flag)
		ft_printf("aff : %c\n", r);
	process->pc += 3;
}
