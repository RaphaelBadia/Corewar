/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:40:52 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/20 18:57:18 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <ft_printf.h>

void	ld(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	unsigned int	octal;
	unsigned int	offset;
	int				reg;
	int				param;

	pc = process->pc;
	octal = vm->map[PTR(pc + 1)] >> 6;
	if (octal == DIR_CODE)
		param = get_dir(vm, pc + 2, 0);
	else
		param = get_indir(vm, pc, pc + 2, 1);
	offset = octal == DIR_CODE ? 6 : 4;
	reg = vm->map[PTR(pc + offset)];
	if (vm->flag & verbose)
		ft_printf("P %4d | ld %d r%d\n", process->id, param, reg);
	if (!(process->r[reg - 1] = param))
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += offset + 1;
}
