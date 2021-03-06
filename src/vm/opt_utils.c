/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 21:48:30 by jye               #+#    #+#             */
/*   Updated: 2017/03/18 22:17:31 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <graphic.h>

static int			test_reg(t_vm *vm, unsigned char byte_code,
						unsigned char octal_code, unsigned int pc)
{
	unsigned char	octal[3];
	unsigned int	offset;
	int				i;

	octal[0] = octal_code >> 6;
	octal[1] = (octal_code >> 4) & 3;
	octal[2] = (octal_code >> 2) & 3;
	if (octal[0] != REG_CODE && octal[1] != REG_CODE && octal[2] != REG_CODE)
		return (0);
	offset = 2;
	i = -1;
	while (++i < g_op_tab[byte_code].argc)
		if (octal[i] != REG_CODE)
		{
			if (octal[i] == DIR_CODE)
				offset += g_op_tab[byte_code].label_size ? 2 : 4;
			else
				offset += 2;
			continue ;
		}
		else if (vm->map[PTR(pc + offset)] && vm->map[PTR(pc + offset)] <= 16)
			offset += 1;
		else
			return (1);
	return (0);
}

static unsigned int	check_octal(t_vm *vm, t_process *process)
{
	int				i;
	unsigned int	offset;
	unsigned char	byte_code;
	unsigned char	octal;
	unsigned char	octal_code;

	byte_code = process->op_code;
	i = 0;
	offset = 6;
	if (!g_op_tab[byte_code].octal)
		return (0);
	octal_code = vm->map[PTR(process->pc + 1)];
	while (i < g_op_tab[byte_code].argc)
	{
		octal = (octal_code >> offset) & 3;
		if (!((g_op_tab[byte_code].argv[i] & T_DIR) && octal == DIR_CODE) &&
			!((g_op_tab[byte_code].argv[i] & T_REG) && octal == REG_CODE) &&
			!((g_op_tab[byte_code].argv[i] & T_IND) && octal == IND_CODE))
			return (nskip(byte_code, octal_code));
		++i;
		offset -= 2;
	}
	if (test_reg(vm, byte_code, octal_code, process->pc))
		return (nskip(byte_code, octal_code));
	return (0);
}

static void			get_opt(t_vm *vm, t_process *process,
							unsigned char byte_code, unsigned int octal_skip)
{
	if (process->op_code)
		return ;
	if (byte_code > 0 && byte_code <= 16)
	{
		process->op_code = byte_code;
		process->exec_cycle = g_op_tab[byte_code].cycles + vm->cycle;
		highlight(vm, process->pc, 1, -1);
	}
	else if (!octal_skip)
	{
		unlight(vm, process->pc, 1);
		if (++process->pc >= MEM_SIZE)
			process->pc = process->pc % MEM_SIZE;
		byte_code = vm->map[PTR(process->pc)];
		highlight(vm, process->pc, 1, -1);
	}
}

static void			exec_opt(t_vm *vm, t_process *process)
{
	static void		(*f[])() = {NULL, &live, &ld, &st, &add, &sub, &and,
								&or, &xor, &zjmp, &ldi, &sti, &frk, &lld,
								&lldi, &lfork, &aff};
	unsigned int	octal_skip;
	unsigned char	byte_code;

	unlight(vm, process->pc, 1);
	if (!(octal_skip = check_octal(vm, process)))
		f[process->op_code](vm, process);
	else
		process->pc += octal_skip;
	process->op_code = 0;
	byte_code = vm->map[PTR(process->pc)];
	get_opt(vm, process, byte_code, octal_skip);
}

void				check_opt(t_vm *vm)
{
	unsigned char	byte_code;
	t_process		*cp;
	t_lst			*process;

	process = vm->process;
	while (process)
	{
		cp = process->data;
		byte_code = vm->map[PTR(cp->pc)];
		get_opt(vm, cp, byte_code, 0);
		if (cp->op_code && cp->exec_cycle == vm->cycle)
			exec_opt(vm, cp);
		process = process->next;
	}
}
