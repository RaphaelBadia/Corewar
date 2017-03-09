/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:25:28 by jye               #+#    #+#             */
/*   Updated: 2017/03/09 21:17:24 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "vm.h"

static int		reset_flag(t_vm *vm, unsigned int flag)
{
	if (flag == dump && (vm->flag |= flag))
	{
		if (vm->flag & visual)
			vm->flag ^= visual;
		if (vm->flag & stop)
			vm->flag ^= stop;
	}
	else if (flag == stop && (vm->flag |= flag))
	{
		if (vm->flag & visual)
			vm->flag ^= visual;
		if (vm->flag & dump)
			vm->flag ^= dump;
	}
	else if (flag == visual && (vm->flag |= flag))
	{
		if (vm->flag & dump)
			vm->flag ^= dump;
		if (vm->flag & stop)
			vm->flag ^= stop;
	}
	return (1);
}

void			set_flag_arg(t_vm *vm, t_arg *arg)
{
	if (arg->i + 1 > arg->ac)
		usage(arg->av[0]);
	if (vm->flag & dump)
		vm->dump_cycle = atoi(arg->av[++arg->i]);
	if (vm->flag & stop)
		vm->stop_cycle = atoi(arg->av[++arg->i]);
	if (vm->flag & verbose)
		vm->verbose_level = atoi(arg->av[++arg->i]);
}

void			set_flag(t_vm *vm, t_arg *arg)
{
	while (++arg->i < arg->ac)
		if (!strcmp(arg->av[arg->i], DMP_FLAG) && reset_flag(vm, dump))
			set_flag_arg(vm, arg);
		else if (!strcmp(arg->av[arg->i], VIS_FLAG))
			reset_flag(vm, visual);
		else if (!strcmp(arg->av[arg->i], AFF_FLAG))
			vm->flag |= aff_flag;
		else if (!strcmp(arg->av[arg->i], STOP_FLAG) && reset_flag(vm, stop))
			set_flag_arg(vm, arg);
		else if (!strcmp(arg->av[arg->i], VERB_FLAG))
			set_flag_arg(vm, arg);
		else
			return ;
}
