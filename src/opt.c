/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:00:01 by jye               #+#    #+#             */
/*   Updated: 2017/02/26 20:49:39 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
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
		param = vm->map[PTR(data[0])];
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
		param = (vm->map[PTR(pc + (indir % IDX_MOD))] << 24) |	\
				(vm->map[PTR(pc + 1 + (indir % IDX_MOD))] << 16) |	\
				(vm->map[PTR(pc + 2 + (indir % IDX_MOD))] << 8) |	\
				(vm->map[PTR(pc + 3 + (indir % IDX_MOD))]);
	}
	return (param);
}

unsigned int	get_lparam(t_vm *vm, unsigned int pc, int data[3])
{
	unsigned int	param;
	short			indir;

	param = 0;
	if (data[1] == REG_CODE)
		param = vm->map[PTR(data[0])];
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
	octal = vm->map[PTR(i + 1)] >> 6;
	if (octal == DIR_CODE)
	{
		param = get_param(vm, i, (int[3]){i + 2, DIR_CODE, 0});
		if (vm->map[PTR(i + 6)] > 0 && vm->map[PTR(i + 6)] <= 16 && !(process->r[vm->map[PTR(i + 6)] - 1] = param))
			process->carry = 1;
		else
			process->carry = 0;
		process->pc += 7;
	}
	else if (octal == IND_CODE)
	{
		param = get_param(vm, i, (int[3]){i + 2, IND_CODE, 0});
		if (vm->map[PTR(i + 4)] > 0 && vm->map[PTR(i + 4)] <= 16 && !(process->r[vm->map[PTR(i + 4)] - 1] = param))
			process->carry = 1;
		else
			process->carry = 0;
		process->pc += 5;
	}
}

void	write_mem(t_vm *vm, unsigned int pc, unsigned int value)
{
	vm->map[PTR(pc)] = (value >> 24);
	vm->map[PTR(pc + 1)] = (value >> 16) & 0xff;
	vm->map[PTR(pc + 2)] = (value >> 8) & 0xff;
	vm->map[PTR(pc + 3)] = (value) & 0xff;
}

void	st(t_vm *vm, t_process *process)
{
	unsigned char	octal;
	unsigned int	param;
	unsigned int	reg_val;
	unsigned int	i;

	i = process->pc;
	octal = (vm->map[PTR(i + 1)] >> 4) & 3;
	if (vm->map[PTR(i + 2)] > 0 && vm->map[PTR(i + 2)] <= 16)
		reg_val = process->r[vm->map[PTR(i + 2)] - 1];
	if (octal == REG_CODE)
	{
		param = get_param(vm, i, (int[3]){i + 3, REG_CODE, 0});
		if (param > 0 && param <= 16)
			process->r[param - 1] = reg_val;
		process->pc += 4;
	}
	else if (octal == IND_CODE)
	{
		param = get_param(vm, i, (int[3]){i + 3, DIR_CODE, 1});
		write_mem(vm, i + (param % IDX_MOD), reg_val);
		process->pc += 5;
	}
}

void	add(t_vm *vm, t_process *process)
{
	unsigned int	param[3];
	unsigned int	reg_val[2];
	unsigned int	i;

	i = process->pc;
	param[0] = get_param(vm, i, (int[3]){i + 2, REG_CODE, 0});
	param[1] = get_param(vm, i, (int[3]){i + 3, REG_CODE, 0});
	param[2] = get_param(vm, i, (int[3]){i + 4, REG_CODE, 0});
	if (param[0] > 0 && param[0] <= 16)
		reg_val[0] = process->r[param[0] - 1];
	else
		reg_val[0] = 0;
	if (param[1] > 0 && param[1] <= 16)
		reg_val[1] = process->r[param[1] - 1];
	else
		reg_val[1] = 0;
	if (param[2] > 0 && param[2] <= 16)
	{
		if ((process->r[param[2] - 1] = reg_val[0] + reg_val[1]) == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->carry = 0;
}

void	sub(t_vm *vm, t_process *process)
{
	unsigned int	param[3];
	unsigned int	reg_val[2];
	unsigned int	i;

	i = process->pc;
	param[0] = get_param(vm, i, (int[3]){i + 2, REG_CODE, 0});
	param[1] = get_param(vm, i, (int[3]){i + 3, REG_CODE, 0});
	param[2] = get_param(vm, i, (int[3]){i + 4, REG_CODE, 0});
	if (param[0] > 0 && param[0] <= 16)
		reg_val[0] = process->r[param[0] - 1];
	else
		reg_val[0] = 0;
	if (param[1] > 0 && param[1] <= 16)
		reg_val[1] = process->r[param[1] - 1];
	else
		reg_val[1] = 0;
	if (param[2] > 0 && param[2] <= 16)
	{
		if ((process->r[param[2] - 1] = reg_val[0] - reg_val[1]) == 0)
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->carry = 0;
}

void	and(t_vm *vm, t_process *process)
{
	unsigned int	param[2];
	unsigned int	offset;
	unsigned int	i;
	unsigned int	pc;
	unsigned char	octal[2];

	pc = process->pc;
	i = 0;
	octal[0] = vm->map[PTR(pc + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc + 2)] >> 4) & 3;
	offset = 2;
	while (i < 2)
	{
		if (octal[i] == REG_CODE)
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, DIR_CODE, 0});
			if (param[i] > 0 && param[i] <= 16)
				param[i] = process->r[param[i] - 1];
			offset += 1;
		}
		else if (octal[i] == DIR_CODE)
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, DIR_CODE, 0});
			offset += 4;
		}
		else
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, IND_CODE, 0});
			offset += 2;
		}
		++i;
	}
	if ((i = vm->map[PTR(offset + pc)]) > 0 && i <= 17)
	{
		if (!(process->r[i - 1] = param[0] & param[1]))
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->carry = 0;
}

void	or(t_vm *vm, t_process *process)
{
	unsigned int	param[2];
	unsigned int	offset;
	unsigned int	i;
	unsigned int	pc;
	unsigned char	octal[2];

	pc = process->pc;
	i = 0;
	octal[0] = vm->map[PTR(pc + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc + 1)] >> 4) & 3;
	offset = 2;
	while (i < 2)
	{
		if (octal[i] == REG_CODE)
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, DIR_CODE, 0});
			if (param[i] > 0 && param[i] <= 16)
				param[i] = process->r[param[i] - 1];
			offset += 1;
		}
		else if (octal[i] == DIR_CODE)
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, DIR_CODE, 0});
			offset += 4;
		}
		else
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, IND_CODE, 0});
			offset += 2;
		}
		++i;
	}
	if ((i = vm->map[offset + pc]) > 0 && i <= 17)
	{
		if (!(process->r[i - 1] = param[0] | param[1]))
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->carry = 0;
}

void	xor(t_vm *vm, t_process *process)
{
	unsigned int	param[2];
	unsigned int	offset;
	unsigned int	i;
	unsigned int	pc;
	unsigned char	octal[2];

	pc = process->pc;
	i = 0;
	octal[0] = vm->map[pc + 1] >> 6;
	octal[1] = (vm->map[pc + 2] >> 4) & 3;
	offset = 2;
	while (i < 2)
	{
		if (octal[i] == REG_CODE)
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, DIR_CODE, 0});
			if (param[i] > 0 && param[i] <= 16)
				param[i] = process->r[param[i] - 1];
			offset += 1;
		}
		else if (octal[i] == DIR_CODE)
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, DIR_CODE, 0});
			offset += 4;
		}
		else
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, IND_CODE, 0});
			offset += 2;
		}
		++i;
	}
	if ((i = vm->map[PTR(offset + pc)]) > 0 && i <= 17)
	{
		if (!(process->r[i - 1] = param[0] ^ param[1]))
			process->carry = 1;
		else
			process->carry = 0;
	}
	else
		process->carry = 0;
}

void	zjmp(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	short			param;

	pc = process->pc;
	param = get_param(vm, pc, (int[3]){pc + 1, DIR_CODE, 1});
	if (process->carry)
		process->pc += param % IDX_MOD;
	else
		process->pc += 3;
}

void	ldi(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	unsigned int	i;
	unsigned int	offset;
	unsigned int	param[2];
	unsigned char	octal[2];

	pc = process->pc;
	i = 0;
	octal[0] = vm->map[PTR(pc + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc + 1)] >> 4) & 3;
	offset = 2;
	while (i < 2)
	{
		if (octal[i] == REG_CODE)
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, DIR_CODE, 0});
			if (param[i] > 0 && param[i] <= 16)
				param[i] = process->r[param[i] - 1];
			offset += 1;
		}
		else if (octal[i] == DIR_CODE)
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, DIR_CODE, 0});
			offset += 4;
		}
		else
		{
			param[i] = get_param(vm, pc, (int[3]){pc + offset, IND_CODE, 0});
			offset += 2;
		}
		++i;
	}
	if ((i = vm->map[PTR(offset + pc)]) > 0 && i <= 17)
		process->r[i - 1] = get_param(vm, pc, (int[3]){pc + ((param[0] + param[1]) % IDX_MOD), IND_CODE, 0});
}

void	sti(t_vm *vm, t_process *process)
{

}

void	fork(t_vm *vm, t_process *process, t_lst *lst_process)
{
	unsigned int	target;
	unsigned int	i;
	t_process		*new_p;

	if (!(new_p = malloc(sizeof(t_process))))
	{
		perror(ERROR);
		exit(1);
	}
	i = process->pc;
	target = get_param(vm, i, (int[3]){i + 1, DIR_CODE, 1});
	memcpy(new_p, process, sizeof(t_process));
	new_p->pc = i + target;
	push_lst__(&lst_process, new_p);
	process->pc += 5;
}
