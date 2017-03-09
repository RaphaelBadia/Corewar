/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:18:26 by jye               #+#    #+#             */
/*   Updated: 2017/03/09 16:47:05 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "vm.h"

/*
** data[0] = to_get index, data[1] = octal, data[2] = label
*/

void			st_param(t_vm *vm, unsigned int pc, unsigned int val)
{
	vm->map[PTR(pc)] = val >> 24;
	vm->map[PTR(pc + 1)] = (val >> 16) & 0xff;
	vm->map[PTR(pc + 2)] = (val >> 8) & 0xff;
	vm->map[PTR(pc + 3)] = val & 0xff;
}

int				get_param(t_vm *vm, unsigned int pc, int data[3])
{
	int		param;
	short	indir;

	param = 0;
	if (data[1] == REG_CODE)
		param = vm->map[PTR(data[0])];
	else if (data[1] == DIR_CODE)
	{
		if (data[2])
			param = (vm->map[PTR(data[0])] << 8) | (vm->map[PTR(data[0] + 1)]);
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

int	 			get_lparam(t_vm *vm, unsigned int pc, int data[3])
{
	int		param;
	short	indir;

	param = 0;
	if (data[1] == REG_CODE)
		param = vm->map[PTR(data[0])];
	else if (data[1] == DIR_CODE)
	{
		if (data[2])
			param = (vm->map[PTR(data[0])] << 8) | (vm->map[PTR(data[0] + 1)]);
		else
			param = (vm->map[PTR(data[0])] << 24) |		\
				(vm->map[PTR(data[0] + 1)] << 16) |		\
				(vm->map[PTR(data[0] + 2)] << 8) |		\
				(vm->map[PTR(data[0] + 3)]);
	}
	else if (data[1] == IND_CODE)
	{
		indir = (vm->map[PTR(data[0])] << 8) | (vm->map[PTR(data[0] + 1)]);
		param = (vm->map[PTR(pc + (indir))] << 24) |	\
			(vm->map[PTR(pc + 1 + (indir))] << 16) |	\
			(vm->map[PTR(pc + 2 + (indir))] << 8) |	\
			(vm->map[PTR(pc + 3 + (indir))]);
	}
	return (param);
}

int				test_reg(t_vm *vm, unsigned char byte_code,
						unsigned char octal_code, unsigned int pc)
{
	unsigned char	octal[3];
	unsigned int	offset;
	int				i;

	octal[0] = octal_code >> 6;
	octal[1] = (octal_code >> 4) & 3;
	octal[2] = (octal_code >> 2) & 3;
	if (octal[0] != REG_CODE &&
		octal[1] != REG_CODE &&
		octal[2] != REG_CODE)
		return (0);
	offset = 2;
	i = -1;
	while (++i < g_op_tab[byte_code].argc)
	{
		if (octal[i] != REG_CODE)
		{
			if (octal[i] == DIR_CODE)
				offset += g_op_tab[byte_code].label_size ? 2 : 4;
			else
				offset += 2;
			continue ;
		}
		if (vm->map[PTR(pc + offset)] &&
			vm->map[PTR(pc + offset)] <= REG_NUMBER)
			offset += 1;
		else
			return (1);
	}
	return (0);
}

unsigned int	nskip(unsigned char byte_code, unsigned char octal_code)
{
	int				i;
	unsigned int	offset;
	unsigned int	skip;
	unsigned char	octal;

	i = 0;
	offset = 6;
	skip = 2;
	while (i < g_op_tab[byte_code].argc)
	{
		octal = (octal_code >> offset) & 3;
		if (octal == DIR_CODE)
		{
			if (g_op_tab[byte_code].label_size)
				skip += 2;
			else
				skip += 4;
		}
		else if (octal == REG_CODE)
			skip += 1;
		else if (octal == IND_CODE)
			skip += 2;
		++i;
		offset -= 2;
	}
	return (skip);
}
