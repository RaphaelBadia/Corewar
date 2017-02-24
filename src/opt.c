/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:00:01 by jye               #+#    #+#             */
/*   Updated: 2017/02/24 18:56:08 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>
# define GET_UINT32(buff, i)					\
	((*(buff + (i % MEM_SIZE)) << 24) |			\
	 (*(buff + (i % MEM_SIZE + 1)) << 16) |		\
	 (*(buff + (i % MEM_SIZE + 2)) << 8) |		\
	 (*(buff + (i % MEM_SIZE + 3))))
# define GET_UINT16(buff, i)					\
	((*(buff + (i % MEM_SIZE)) << 8) |			\
	 (*(buff + (i % MEM_SIZE + 1))))

void	live(t_vm *vm, t_process *process)
{
	unsigned int	id_player;
	unsigned int	i;

	process->last_live = vm->cycle;
	process->op_code = 0;
	process->exec_cycle = 0;
	id_player = GET_UINT32(vm->map, process->pc + 1);
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
	short			indir;

	process->last_live = vm->cycle;
	process->op_code = 0;
	process->exec_cycle = 0;
	i = process->pc;
	octal = vm->map[i + 1] >> 6;
	if (octal == DIR_CODE)
	{
		param = GET_UINT32(vm->map, i + 2);
		if (vm->map[i + 3] < 16)
			process->r[vm->map[i + 6] - 1] = param;
		process->pc += 7;
	}
	else
	{
		indir = GET_UINT16(vm->map, i + 2);
		param = GET_UINT32(vm->map, i + indir);
		if (vm->map[i + 3] < 16)
			process->r[vm->map[i + 4] - 1] = param;
		process->pc += 5;
	}
}
