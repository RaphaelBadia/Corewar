/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:00:01 by jye               #+#    #+#             */
/*   Updated: 2017/03/02 20:55:57 by jye              ###   ########.fr       */
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
	int				i;
	int				id_player;

	pc = process->pc;
	id_player = get_param(vm, pc, (int[3]){pc + 1, DIR_CODE, 0});
	while (i < vm->nb_player)
	{
		if (vm->champ[i].id_player == id_player)
			vm->champ[i].last_live = vm->cycle;
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
	if (!(reg > 0 && reg <= 16) && (process->pc += offset + 1))
		return ;
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
	process->pc += offset;
	if (!(reg > 0 && reg <= 16))
		return ;
	reg = process->r[reg - 1];
	if (octal == REG_CODE)
	{
		param = get_param(vm, pc, (int[3]){pc + 3, REG_CODE, 0});
		if (param > 0 && param <= 16)
			process->r[param - 1] = reg;
	}
	else
	{
		param = get_param(vm, pc, (int[3]){pc + 3, DIR_CODE, 1});
		st_param(vm, pc + param, reg);
	}
}

void	add(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	int				r[3];

	pc = process->pc;
	r[0] = get_param(vm, pc, (int[3]){pc + 2, REG_CODE, 0});
	r[1] = get_param(vm, pc, (int[3]){pc + 3, REG_CODE, 0});
	r[2] = get_param(vm, pc, (int[3]){pc + 4, REG_CODE, 0});
	if (!(r[0] > 0 && r[0] <= 16
		&& r[1] > 0 && r[1] <= 16
		&& r[2] > 0 && r[2] <= 16))
	{
		process->pc += 5;
		return ;
	}
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
	if (!(r[0] > 0 && r[0] <= 16
		&& r[1] > 0 && r[1] <= 16
		&& r[2] > 0 && r[2] <= 16))
	{
		process->pc += 5;
		return ;
	}
	r[0] = process->r[r[0] - 1];
	r[1] = process->r[r[1] - 1];
	if ((process->r[r[2] - 1] = r[0] + r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += 5;
}

void	and(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	int				i;
	int				r[3];

	pc = process->pc;
	i = -1;
}
