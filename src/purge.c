/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 22:17:01 by jye               #+#    #+#             */
/*   Updated: 2017/03/09 22:27:33 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>

static void	pop_next__(t_vm *vm, unsigned long last_check)
{
	t_process	*pro;
	t_lst		*cp;

	cp = vm->process;
	while (cp)
	{
		pro = cp->data;
		if (pro->last_live == 0 || (pro->last_live < last_check))
		{
			vm->nb_process -= 1;
			pop_lst__(&cp, &free);
		}
		else
			cp = cp->next;
	}
}

void		purge_process(t_vm *vm, unsigned long last_check)
{
	t_process	*pro;
	t_lst		*cp;

	if (vm->cycle == 0)
		return ;
	else if (vm->cycle_to_die & 0xf0000000)
	{
		while (vm->process)
			pop_lst__(&vm->process, &free);
		return ;
	}
	cp = vm->process;
	while (cp && (pro = cp->data))
	{
		if (pro->last_live == 0 || (pro->last_live < last_check))
		{
			vm->nb_process -= 1;
			pop_lst__(&cp, &free);
		}
		else
			break ;
	}
	vm->process = cp;
	pop_next__(vm, last_check);
}
