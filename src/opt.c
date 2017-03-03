/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:00:01 by jye               #+#    #+#             */
/*   Updated: 2017/03/03 17:54:31 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "vm.h"

void	live(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	unsigned int	id_player;
	int				i;

	pc = process->pc;
	id_player = get_param(vm, pc, (int[3]){pc + 1, DIR_CODE, 0});
	i = 0;
	while (i < vm->nb_player)
	{
		if (vm->champ[i].id_player == id_player)
		{
			vm->champ[i].live += 1;
			vm->champ[i].last_live = vm->cycle;
		}
		++i;
	}
	process->last_live = vm->cycle;
	process->pc += 5;
}

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
		param = get_param(vm, pc, (int[3]){pc + 2, DIR_CODE, 0});
	else
		param = get_param(vm, pc, (int[3]){pc + 2, IND_CODE, 0});
	offset = octal == DIR_CODE ? 6 : 4;
	reg = get_param(vm, pc, (int[3]){pc + offset, REG_CODE, 0});
	if (!(process->r[reg - 1] = param))
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += offset + 1;
}

void	st(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	unsigned int	octal;
	unsigned int	reg;
	unsigned int	offset;
	int				param;

	pc = process->pc;
	octal = (vm->map[PTR(pc + 1)] >> 4) & 3;
	reg = get_param(vm, pc, (int[3]){pc + 2, REG_CODE, 0});
	offset = octal == REG_CODE ? 4 : 5;
	reg = process->r[reg - 1];
	if (octal == REG_CODE)
	{
		param = get_param(vm, pc, (int[3]){pc + 3, REG_CODE, 0});
		process->r[param - 1] = reg;
	}
	else
	{
		param = get_param(vm, pc, (int[3]){pc + 3, DIR_CODE, 1});
		st_param(vm, pc + param, reg);
	}
	process->pc += offset;
}

void	add(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	int				r[3];

	pc = process->pc;
	r[0] = get_param(vm, pc, (int[3]){pc + 2, REG_CODE, 0});
	r[1] = get_param(vm, pc, (int[3]){pc + 3, REG_CODE, 0});
	r[2] = get_param(vm, pc, (int[3]){pc + 4, REG_CODE, 0});
	r[0] = process->r[r[0] - 1];
	r[1] = process->r[r[1] - 1];
	if ((process->r[r[2] - 1] = r[0] + r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += 5;
}

void	sub(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	int				r[3];

	pc = process->pc;
	r[0] = get_param(vm, pc, (int[3]){pc + 2, REG_CODE, 0});
	r[1] = get_param(vm, pc, (int[3]){pc + 3, REG_CODE, 0});
	r[2] = get_param(vm, pc, (int[3]){pc + 4, REG_CODE, 0});
	r[0] = process->r[r[0] - 1];
	r[1] = process->r[r[1] - 1];
	if ((process->r[r[2] - 1] = r[0] - r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += 5;
}

void	and(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	unsigned int	offset;
	int				i;
	unsigned int	r[3];
	unsigned char	octal;

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	i = 0;
	offset = 6;
	while (i < 2)
	{
		octal = vm->map[PTR(pc[0] + 1)] >> offset & 3;
		if (octal == REG_CODE)
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], REG_CODE, 0});
			pc[1] += 1;
			r[i] = process->r[r[i] - 1];
		}
		else if (octal == DIR_CODE)
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], DIR_CODE, 0});
			pc[1] += 4;
		}
		else
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], IND_CODE, 0});
			pc[1] += 2;
		}
		offset -= 2;
		++i;
	}
	r[2] = get_param(vm, pc[0], (int[3]){pc[1], REG_CODE, 0});
	if ((process->r[r[2] - 1] = r[0] & r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc = pc[1] + 1;
}

void	or(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	unsigned int	offset;
	int				i;
	unsigned int	r[3];
	unsigned char	octal;

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	i = 0;
	offset = 6;
	while (i < 2)
	{
		octal = vm->map[PTR(pc[0] + 1)] >> offset & 3;
		if (octal == REG_CODE)
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], REG_CODE, 0});
			pc[1] += 1;
			r[i] = process->r[r[i] - 1];
		}
		else if (octal == DIR_CODE)
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], DIR_CODE, 0});
			pc[1] += 4;
		}
		else
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], IND_CODE, 0});
			pc[1] += 2;
		}
		offset -= 2;
		++i;
	}
	r[2] = get_param(vm, pc[0], (int[3]){pc[1], REG_CODE, 0});
	if ((process->r[r[2] - 1] = r[0] | r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc = pc[1] + 1;
}

void	xor(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	unsigned int	offset;
	int				i;
	unsigned int	r[3];
	unsigned char	octal;

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	i = 0;
	offset = 6;
	while (i < 2)
	{
		octal = vm->map[PTR(pc[0] + 1)] >> offset & 3;
		if (octal == REG_CODE)
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], REG_CODE, 0});
			pc[1] += 1;
			r[i] = process->r[r[i] - 1];
		}
		else if (octal == DIR_CODE)
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], DIR_CODE, 0});
			pc[1] += 4;
		}
		else
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], IND_CODE, 0});
			pc[1] += 2;
		}
		offset -= 2;
		++i;
	}
	r[2] = get_param(vm, pc[0], (int[3]){pc[1], REG_CODE, 0});
	if ((process->r[r[2] - 1] = r[0] ^ r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc = pc[1] + 1;
}

void	zjmp(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	short			jump;

	pc = process->pc;
	jump = get_param(vm, pc, (int[3]){pc + 1, DIR_CODE, 1});
	if (process->carry)
		process->pc += jump;
	else
		process->pc += 3;
}
