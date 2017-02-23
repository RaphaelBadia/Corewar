/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:00:01 by jye               #+#    #+#             */
/*   Updated: 2017/02/23 22:59:03 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdio.h>
# define GET_UINT32(buff, i)					\
	((*(buff + i) << 24) |						\
	 (*(buff + i + 1) << 16) |					\
	 (*(buff + i + 2) << 8) |					\
	 (*(buff + i + 3)))
# define GET_UINT16(buff, i)					\
	((*(buff + i) << 8) |						\
	 (*(buff + i + 1)))

void	live(t_vm *vm, t_process *process)
{
	unsigned int	id_player;
	unsigned int	i;

	process->last_live = vm->cycle;
	process->op_code = 0;
	process->exec_cycle = 0;
	process->op_code = 0;
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
