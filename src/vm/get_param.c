/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:59:06 by jye               #+#    #+#             */
/*   Updated: 2017/03/21 22:03:11 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>

void			st_param(t_vm *vm, unsigned int pc, unsigned int val)
{
	vm->map[PTR(pc)] = val >> 24;
	vm->map[PTR(pc + 1)] = (val >> 16) & 0xff;
	vm->map[PTR(pc + 2)] = (val >> 8) & 0xff;
	vm->map[PTR(pc + 3)] = val & 0xff;
}

int				get_indir(t_vm *vm, unsigned int pc,
						unsigned int i, unsigned int mod)
{
	int		param;
	short	indir;

	param = 0;
	indir = (vm->map[PTR(i)] << 8) | (vm->map[PTR(i + 1)]);
	if (mod)
		param = (vm->map[PTR(pc + (indir % IDX_MOD))] << 24) |
			(vm->map[PTR(pc + 1 + (indir % IDX_MOD))] << 16) |
			(vm->map[PTR(pc + 2 + (indir % IDX_MOD))] << 8) |
			(vm->map[PTR(pc + 3 + (indir % IDX_MOD))]);
	else
		param = (vm->map[PTR(pc + (indir))] << 24) |
			(vm->map[PTR(pc + 1 + (indir))] << 16) |
			(vm->map[PTR(pc + 2 + (indir))] << 8) |
			(vm->map[PTR(pc + 3 + (indir))]);
	return (param);
}

int				get_dir(t_vm *vm, unsigned int pc, unsigned int label)
{
	int		param;

	if (label)
		param = (short)((vm->map[PTR(pc)] << 8) | (vm->map[PTR(pc + 1)]));
	else
		param = (vm->map[PTR(pc)] << 24) |
			(vm->map[PTR(pc + 1)] << 16) |
			(vm->map[PTR(pc + 2)] << 8) |
			(vm->map[PTR(pc + 3)]);
	return (param);
}

int				get_param(t_vm *vm, t_process *process, unsigned int *pc,
							int data[3])
{
	int r;

	if (data[0] == REG_CODE)
	{
		r = vm->map[PTR(pc[1])];
		pc[1] += 1;
		r = process->r[r - 1];
	}
	else if (data[0] == DIR_CODE)
	{
		r = get_dir(vm, pc[1], data[1]);
		pc[1] += data[1] ? 2 : 4;
	}
	else
	{
		r = get_indir(vm, pc[0], pc[1], data[2]);
		pc[1] += 2;
	}
	return (r);
}
