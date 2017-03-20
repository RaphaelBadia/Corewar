/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 22:17:01 by jye               #+#    #+#             */
/*   Updated: 2017/03/20 19:11:21 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>
#include <graphic.h>

static void	kill_process(t_vm *vm, t_lst **node_to_kill,
							t_process *pro, unsigned long last_check)
{
	unlight(vm, pro->pc, 1);
	vm->nb_process -= 1;
	if (vm->flag & verbose)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				pro->id, vm->cycle_to_die + 50 + last_check - pro->last_live,
				vm->cycle_to_die + 50);
	pop_lst__(node_to_kill, &free);
}

static void	pop_next__(t_vm *vm, unsigned long last_check)
{
	t_process	*pro;
	t_lst		*cp;

	cp = vm->process;
	while (cp)
	{
		pro = cp->data;
		if ((pro->last_live <= last_check))
			kill_process(vm, &cp, pro, last_check);
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
		while (vm->process && (pro = vm->process->data))
			kill_process(vm, &vm->process, pro, last_check);
		return ;
	}
	cp = vm->process;
	while (cp && (pro = cp->data))
	{
		if ((pro->last_live <= last_check))
			kill_process(vm, &cp, pro, last_check);
		else
			break ;
	}
	vm->process = cp;
	pop_next__(vm, last_check);
}
