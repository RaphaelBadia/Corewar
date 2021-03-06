/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:25:28 by jye               #+#    #+#             */
/*   Updated: 2017/03/23 14:59:46 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <vm.h>
#include <libft.h>

static int		reset_flag(t_vm *vm, unsigned int flag)
{
	if (flag == dump && (vm->flag |= flag))
		vm->flag &= (0xffff ^ (visual | stop));
	else if (flag == stop && (vm->flag |= flag))
		vm->flag &= (0xffff ^ (visual | dump));
	else if (flag == visual && (vm->flag |= flag))
		vm->flag &= (0xffff ^ (dump | stop | verbose | aff_flag));
	return (1);
}

void			set_flag_arg(t_vm *vm, t_arg *arg)
{
	if (arg->i + 1 > arg->ac - 1)
		usage(arg->av[0]);
	if (vm->flag & dump)
		vm->dump_cycle = ft_atoi(arg->av[++arg->i]);
	if (vm->flag & stop)
		if ((vm->stop_cycle = ft_atoi(arg->av[++arg->i])) <= 0)
			vm->flag ^= stop;
}

void			set_flag(t_vm *vm, t_arg *arg)
{
	while (++arg->i < arg->ac)
		if (!ft_strcmp(arg->av[arg->i], DMP_FLAG) && reset_flag(vm, dump))
			set_flag_arg(vm, arg);
		else if (!ft_strcmp(arg->av[arg->i], VIS_FLAG))
			reset_flag(vm, visual);
		else if (!ft_strcmp(arg->av[arg->i], AFF_FLAG))
			vm->flag |= aff_flag;
		else if (!ft_strcmp(arg->av[arg->i], STOP_FLAG) && reset_flag(vm, stop))
			set_flag_arg(vm, arg);
		else if (!ft_strcmp(arg->av[arg->i], VERB_FLAG))
			vm->flag |= verbose;
		else
			return ;
}
