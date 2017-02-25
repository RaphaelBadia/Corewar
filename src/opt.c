/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:00:01 by jye               #+#    #+#             */
/*   Updated: 2017/02/25 22:52:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** data[0] = to_get index, data[1] = octal, data[2] = label
*/

unsigned int	get_param(t_vm *vm, unsigned int pc, int data[3])
{
	unsigned int	param;
	short			indir;

	param = 0;
	if (data[1] == REG_CODE)
		param = vm->map[PTR(pc)];
	else if (data[1] == DIR_CODE)
	{
		if (data[2])
			param =	(vm->map[PTR(data[0])] << 8) | (vm->map[PTR(data[0] + 1)]);
		else
			param = (vm->map[PTR(data[0])] << 24) |		\
				(vm->map[PTR(data[0] + 1)] << 16) |		\
				(vm->map[PTR(data[0] + 2)] << 8) |		\
				(vm->map[PTR(data[0] + 3)]);
	}
	else if (data[1] == IND_CODE)
	{
		indir = (vm->map[PTR(data[0])] << 8) | (vm->map[PTR(data[0] + 1)]);
		param = (vm->map[PTR(pc + indir)] << 24) |	\
				(vm->map[PTR(pc + 1 + indir)] << 16) |	\
				(vm->map[PTR(pc + 2 + indir)] << 8) |	\
				(vm->map[PTR(pc + 3 + indir)]);
	}
	return (param);
}

void	live(t_vm *vm, t_process *process)
{
	unsigned int	id_player;
	unsigned int	i;

	process->last_live = vm->cycle;
	id_player = get_param(vm, process->pc,
					(int[3]){process->pc + 1, DIR_CODE, 0});
	i = 0;
	while (i < vm->nb_player)
	{
		if (vm->champ[i].id_player == id_player)
		{
			vm->champ[i].last_live = vm->cycle;
			vm->champ[i].live += 1;
			break ;
		}
		++i;
	}
	process->pc += 5;
}

void	ld(t_vm *vm, t_process *process)
{
	unsigned char	octal;
	unsigned int	param;
	unsigned int	i;

	i = process->pc;
	octal = vm->map[i + 1] >> 6;
	if (octal == DIR_CODE)
	{
		param = get_param(vm, i, (int[3]){i + 2, DIR_CODE, 0});
		if (vm->map[i + 3] <= 16)
			process->r[vm->map[i + 6] - 1] = param;
		process->pc += 7;
	}
	else if (octal == IND_CODE)
	{
		param = get_param(vm, i, (int[3]){i + 2, IND_CODE, 0});
		if (vm->map[i + 3] <= 16)
			process->r[vm->map[i + 4] - 1] = param;
		process->pc += 5;
	}
}

void	write_mem(t_vm *vm, unsigned int pc, unsigned int value)
{
	vm->map[pc] = (value >> 24);
	vm->map[pc + 1] = (value >> 16) & 0xff;
	vm->map[pc + 2] = (value >> 8) & 0xff;
	vm->map[pc + 3] = (value) & 0xff;
}

void	st(t_vm *vm, t_process *process)
{
	unsigned char	octal;
	unsigned int	param;
	unsigned int	reg_val;
	unsigned int	i;

	i = process->pc;
	octal = (vm->map[i + 1] >> 4) & 3;
	if (vm->map[i + 2] <= 16)
		reg_val = process->r[vm->map[i + 2] - 1];
	if (octal == REG_CODE)
	{
		param = get_param(vm, i, (int[3]){i + 3, REG_CODE, 0});
		process->pc += 4;
		if (param <= 16)
			param = process->r[param - 1];
	}
	else if (octal == IND_CODE)
	{
		param = get_param(vm, i, (int[3]){i + 3, IND_CODE, 0});
		process->pc += 5;
	}
	write_mem(vm, process->pc + (param % IDX_MOD), reg_val);
}
