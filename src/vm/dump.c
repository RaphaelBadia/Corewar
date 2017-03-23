/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:19:00 by jye               #+#    #+#             */
/*   Updated: 2017/03/23 14:30:36 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <vm.h>

static void	print_map32(unsigned char *map)
{
	int		t;
	short	i;
	int		z;

	t = 0;
	i = 0;
	while (t < 128)
	{
		z = 0;
		while (z < 32)
		{
			ft_printf("%.2hhx", map[i++]);
			++z;
			ft_printf(" ");
		}
		ft_printf("\n");
		++t;
	}
}

void		dump_play(t_vm *vm)
{
	unsigned long	last_check;

	last_check = 0;
	introduce(vm);
	while (vm->process && vm->dump_cycle >= vm->cycle)
	{
		check_opt(vm);
		if (last_check == vm->cycle - vm->cycle_to_die)
		{
			checks(vm);
			purge_process(vm, last_check);
			last_check = vm->cycle;
		}
		vm->cycle += 1;
		if (vm->flag & verbose)
			ft_printf("It is now cycle %ld\n", vm->cycle);
	}
	if (vm->process)
		print_map32(vm->map);
	else
		print_winner(vm);
}
