/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 21:37:22 by jye               #+#    #+#             */
/*   Updated: 2017/03/12 17:58:30 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>
//
#include <string.h>

static t_process	*init_process__(t_vm *vm, unsigned int r1, unsigned int pc)
{
	t_process	*new_p;

	if ((new_p = malloc(sizeof(t_process))) == NULL)
		return (NULL);
	memset(new_p, 0, sizeof(t_process));
	new_p->r[0] = r1;
	new_p->pc = pc;
	new_p->id_player = r1;
	new_p->id = vm->id_track++;
	return (new_p);
}

t_lst				*init_process(t_vm *vm)
{
	unsigned int	i;
	unsigned int	pc;
	t_lst			*process;
	t_process		*cp;

	i = 0;
	process = NULL;
	pc = 0;
	while (i < vm->nb_player)
	{
		if ((cp = init_process__(vm, vm->champ[i].id_player, pc)) == NULL)
			exit(1);
		push_lst__(&process, cp);
		++i;
		pc += MEM_SIZE / vm->nb_player;
	}
	vm->nb_process = vm->nb_player;
	return (process);
}
