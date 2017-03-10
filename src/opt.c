/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:00:01 by jye               #+#    #+#             */
/*   Updated: 2017/03/10 22:23:29 by rbadia           ###   ########.fr       */
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
	id_player = get_dir(vm, pc + 1, 0);
	i = 0;
	while (i < vm->nb_player)
	{
		if (vm->champ[i].id_player == id_player)
		{
			vm->champ[i].last_live = vm->cycle;
			vm->champ[i].live += 1;
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
		param = get_dir(vm, pc + 2, 0);
	else
		param = get_indir(vm, pc, pc + 2, 1);
	offset = octal == DIR_CODE ? 6 : 4;
	reg = vm->map[PTR(pc + offset)];
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
	reg = vm->map[PTR(pc + 2)];
	offset = octal == REG_CODE ? 4 : 5;
	reg = process->r[reg - 1];
	if (octal == REG_CODE)
	{
		param = vm->map[PTR(pc + 3)];
		process->r[param - 1] = reg;
	}
	else
	{
		param = (short)get_dir(vm, pc + 3, 1);
		st_param(vm, pc + (param % IDX_MOD), reg);
	}
	process->pc += offset;
}

void	add(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	int				r[3];

	pc = process->pc;
	r[0] = vm->map[PTR(pc + 2)];
	r[1] = vm->map[PTR(pc + 3)];
	r[2] = vm->map[PTR(pc + 4)];
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
	r[0] = vm->map[PTR(pc + 2)];
	r[1] = vm->map[PTR(pc + 3)];
	r[2] = vm->map[PTR(pc + 4)];
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
	int				i;
	unsigned int	r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	octal[0] = vm->map[PTR(pc[0] + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	i = 0;
	while (i < 2)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i], 0, 1});
		++i;
	}
	r[2] = vm->map[PTR(pc[1])];
	if ((process->r[r[2] - 1] = r[0] & r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc = pc[1] + 1;
}

void	or(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	int				i;
	unsigned int	r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	octal[0] = vm->map[PTR(pc[0] + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	i = 0;
	while (i < 2)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i], 0, 1});
		++i;
	}
	r[2] = vm->map[PTR(pc[1])];
	if ((process->r[r[2] - 1] = r[0] | r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc = pc[1] + 1;
}

void	xor(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	int				i;
	unsigned int	r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	octal[0] = vm->map[PTR(pc[0] + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	i = 0;
	while (i < 2)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i], 0, 1});
		++i;
	}
	r[2] = vm->map[PTR(pc[1])];
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
	jump = (short)get_dir(vm, pc + 1, 1);
	if (process->carry)
		process->pc += (jump % IDX_MOD);
	else
		process->pc += 3;
}

void	ldi(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	int				i;
	int				r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	i = 0;
	octal[0] = vm->map[PTR(pc[0] + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	while (i < 2)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i], 1, 1});
		++i;
	}
	r[2] = vm->map[PTR(pc[1])];
	process->r[r[2] - 1] = get_dir(vm, pc[0] + ((r[0] + r[1]) % IDX_MOD), 0);
	process->pc = pc[1] + 1;
}

void	sti(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	int				i;
	int				r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 3;
	i = 1;

	// r[0] = get_param(vm, pc[0], (int[3]){pc[0] + 2, REG_CODE, 0}); //lol
	r[0] = vm->map[PTR(pc[0] + 2)]; //marche un peu mieux
	r[0] = process->r[r[0] - 1];
	octal[0] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 2) & 3;
	while (i < 3)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i - 1], 1, 1});
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
		p_error();
	pc = process->pc;
	target = get_dir(vm, pc + 1, 1);
	memcpy(new_p, process, sizeof(t_process));
	new_p->pc += (target % IDX_MOD);
	byte_code = vm->map[PTR(new_p->pc)];
	vm->nb_process += 1;
	bool_ = (byte_code > 0 && byte_code <= 16);
	new_p->op_code = bool_ ? byte_code : 0;
	new_p->exec_cycle = bool_ ? g_op_tab[byte_code].cycles + vm->cycle : 0;
	new_p->id = vm->id_track++;
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
		param = get_dir(vm, pc + 2, 0);
	else
		param = get_indir(vm, pc, pc + 2, 0);
	offset = octal == DIR_CODE ? 6 : 4;
	reg = vm->map[PTR(pc + offset)];
	if (!(process->r[reg - 1] = param))
		process->carry = 1;
	else
		process->carry = 0;
	process->pc += offset + 1;
}

void	lldi(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	int				i;
	int				r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	i = 0;
	octal[0] = vm->map[PTR(pc[0] + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	while (i < 2)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i], 1, 1});
		++i;
	}
	r[2] = vm->map[PTR(pc[1])];
	process->r[r[2] - 1] = get_dir(vm, pc[0] + ((r[0] + r[1])), 0);
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
		p_error();
	pc = process->pc;
	target = (short)get_dir(vm, pc + 1, 1);
	memcpy(new_p, process, sizeof(t_process));
	new_p->pc += (target);
	byte_code = vm->map[PTR(new_p->pc)];
	vm->nb_process += 1;
	bool_ = (byte_code > 0 && byte_code <= 16);
	new_p->op_code = bool_ ? byte_code : 0;
	new_p->exec_cycle = bool_ ? g_op_tab[byte_code].cycles + vm->cycle : 0;
	new_p->id = vm->id_track++;
	push_lst__(&vm->process, new_p);
	process->pc += 3;
}
