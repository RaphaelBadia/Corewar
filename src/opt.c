/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:00:01 by jye               #+#    #+#             */
/*   Updated: 2017/03/03 22:47:47 by jye              ###   ########.fr       */
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
			vm->champ[i].last_live = vm->cycle;
		}
		++i;
	}
	vm->live += 1;
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

void	ldi(t_vm *vm, t_process *process)
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
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], DIR_CODE, 1});
			pc[1] += 2;
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
	process->r[r[2] - 1] = get_param(vm, pc[0], (int[3]){pc[0] +	\
				((r[0] + r[1]) % IDX_MOD), DIR_CODE, 0});
	process->pc = pc[1] + 1;
}

void	sti(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	unsigned int	offset;
	int				i;
	int				r[3];
	unsigned char	octal;

	pc[0] = process->pc;
	pc[1] = process->pc + 3;
	i = 1;
	offset = 4;
	r[0] = get_param(vm, pc[0], (int[3]){pc[0] + 2, REG_CODE, 0});
	r[0] = process->r[r[0] - 1];
	while (i < 3)
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
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], DIR_CODE, 1});
			pc[1] += 2;
		}
		else
		{
			r[i] = get_param(vm, pc[0], (int[3]){pc[1], IND_CODE, 0});
			pc[1] += 2;
		}
		offset -= 2;
		++i;
	}
	st_param(vm, pc[0] + ((r[1] + r[2]) % IDX_MOD), r[0]);
	process->pc = pc[1];
}

void	frk(t_vm *vm, t_process *process)
{
	t_process		*new_p;
	unsigned int	pc;
	int				bool_;
	short			target;
	unsigned char	byte_code;

	if (!(new_p = malloc(sizeof(t_process))))
	{
		perror(ERROR);
		exit(1);
	}
	pc = process->pc;
	target = get_param(vm, pc, (int[3]){pc + 1, DIR_CODE, 1});
	memcpy(new_p, process, sizeof(t_process));
	new_p->pc += (target % IDX_MOD);
	byte_code = vm->map[PTR(new_p->pc)];
	vm->nb_process += 1;
	bool_ = (byte_code > 0 && byte_code <= 16);
	new_p->exec_cycle = bool_ ? g_op_tab[byte_code].cycles + vm->cycle : 0;
	new_p->op_code = bool_ ? g_op_tab[byte_code].opcode : 0;
	push_lst__(&vm->process, new_p);
	process->pc += 3;
}

void	lld(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	unsigned int	octal;
	unsigned int	offset;
	int				reg;
	int				param;

	pc = process->pc;
	octal = vm->map[PTR(pc + 1)] >> 6;
	if (octal == DIR_CODE)
		param = get_lparam(vm, pc, (int[3]){pc + 2, DIR_CODE, 0});
	else
		param = get_lparam(vm, pc, (int[3]){pc + 2, IND_CODE, 0});
	offset = octal == DIR_CODE ? 6 : 4;
	reg = get_lparam(vm, pc, (int[3]){pc + offset, REG_CODE, 0});
	if (!(process->r[reg - 1] = param))
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += offset + 1;
}

void	lldi(t_vm *vm, t_process *process)
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
			r[i] = get_lparam(vm, pc[0], (int[3]){pc[1], REG_CODE, 0});
			pc[1] += 1;
			r[i] = process->r[r[i] - 1];
		}
		else if (octal == DIR_CODE)
		{
			r[i] = get_lparam(vm, pc[0], (int[3]){pc[1], DIR_CODE, 1});
			pc[1] += 2;
		}
		else
		{
			r[i] = get_lparam(vm, pc[0], (int[3]){pc[1], IND_CODE, 0});
			pc[1] += 2;
		}
		offset -= 2;
		++i;
	}
	r[2] = get_lparam(vm, pc[0], (int[3]){pc[1], REG_CODE, 0});
	process->r[r[2] - 1] = get_param(vm, pc[0], (int[3]){pc[0] +	\
				((r[0] + r[1])), DIR_CODE, 0});
	process->pc = pc[1] + 1;
}

void	lfork(t_vm *vm, t_process *process)
{
	t_process		*new_p;
	unsigned int	pc;
	int				bool_;
	short			target;
	unsigned char	byte_code;

	if (!(new_p = malloc(sizeof(t_process))))
	{
		perror(ERROR);
		exit(1);
	}
	pc = process->pc;
	target = get_param(vm, pc, (int[3]){pc + 1, DIR_CODE, 1});
	memcpy(new_p, process, sizeof(t_process));
	new_p->pc += (target);
	byte_code = vm->map[PTR(new_p->pc)];
	vm->nb_process += 1;
	bool_ = (byte_code > 0 && byte_code <= 16);
	new_p->exec_cycle = bool_ ? g_op_tab[byte_code].cycles + vm->cycle : 0;
	new_p->op_code = bool_ ? g_op_tab[byte_code].opcode : 0;
	push_lst__(&vm->process, new_p);
	process->pc += 3;
}
