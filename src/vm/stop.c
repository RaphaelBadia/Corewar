/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:18:13 by jye               #+#    #+#             */
/*   Updated: 2017/03/18 18:23:12 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	print_map64(unsigned char *map)
{
	int		t;
	short	i;
	int		z;

	t = 0;
	i = 0;
	while (t < 64)
	{
		z = 0;
		printf("0x%.4hx : ", i);
		while (z < 64)
		{
			printf("%.2hhx", map[i++]);
			++z;
			printf(" ");
		}
		printf("\n");
		++t;
	}
}

void		stop_play(t_vm *vm)
{
	unsigned long	last_check;

	last_check = 0;
	introduce(vm);
	while (vm->process)
	{
		if ((vm->cycle % vm->stop_cycle) == 0)
			print_map64(vm->map);
		check_opt(vm);
		if (last_check == vm->cycle - vm->cycle_to_die)
		{
			checks(vm);
			purge_process(vm, last_check);
			last_check = vm->cycle;
		}
		vm->cycle += 1;
		if (vm->flag & verbose)
			printf("It is now cycle %ld\n", vm->cycle);
	}
	print_winner(vm);
}
