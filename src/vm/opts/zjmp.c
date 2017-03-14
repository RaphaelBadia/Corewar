/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:42:52 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/13 15:47:58 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include "vm.h"

void	zjmp(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	short			jump;

	pc = process->pc;
	jump = (short)get_dir(vm, pc + 1, 1);
	if (vm->flag & verbose)
		printf("P %4d | zjmp %hd ", process->id, jump);
	if (process->carry)
	{
		if (vm->flag & verbose)
			printf("OK\n");
		process->pc += (jump % IDX_MOD);
	}
	else
	{
		if (vm->flag & verbose)
			printf("FAILED\n");
		process->pc += 3;
	}
}
