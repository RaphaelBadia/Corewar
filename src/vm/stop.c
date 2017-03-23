/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:18:13 by jye               #+#    #+#             */
/*   Updated: 2017/03/23 14:46:01 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <vm.h>
#include <ft_printf.h>

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
		ft_printf("0x%.4hx : ", i);
		while (z < 64)
		{
			ft_printf("%.2hhx", map[i++]);
			++z;
			ft_printf(" ");
		}
		ft_printf("\n");
		++t;
	}
}

void		stop_play(t_vm *vm)
{
	unsigned long	last_check;
	char			c;

	last_check = 0;
	introduce(vm);
	while (vm->process)
	{
		if ((vm->cycle % vm->stop_cycle) == 0)
		{
			print_map64(vm->map);
			read(0, &c, 1);
		}
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
	print_winner(vm);
}
