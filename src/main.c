/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 18:08:24 by jye               #+#    #+#             */
/*   Updated: 2017/03/11 22:16:00 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "vm.h"

void	print_map(unsigned char *map)
{
	int		t;
	short	i;

	t = 0;
	i = -1;
	printf("         ");
	while (++i < 64)
		printf("%.2x ", i);
	printf("\n");
	i = 0;
	while (t < 64)
	{
		int z = 0;
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

void	checks(t_vm *vm)
{
	int i;

	i = 0;
	if (vm->cycle == 0)
		return ;
	if (vm->live > 20 && !(vm->checks = 0))
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->flag & verbose)
			printf("Cycle to die is now %d\n", vm->cycle_to_die);
	}
	else if (vm->checks == 9 && !(vm->checks = 0))
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->flag & verbose)
			printf("Cycle to die is now %d\n", vm->cycle_to_die);
	}
	else
		vm->checks += 1;
	while (i < vm->nb_player)
	{
		vm->champ[i].live = 0;
		++i;
	}
	vm->live = 0;
}

void	print_winner(t_vm *vm)
{
	int		i;
	t_champ	*win;

	win= &vm->champ[0];
	i = 0;
	while (i < vm->nb_player)
	{
		if (win->last_live < vm->champ[i].last_live)
			win= &vm->champ[i];
		++i;
	}
	printf("PLAYER %s ID %d (\"%s\") HAS WON WOW.", win->name, win->id_player,
	win->comment);
}

void	play(t_vm *vm)
{
	unsigned long	last_check;

	vm->id_track = 1;
	vm->process = init_process(vm);
	last_check = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	while (vm->process)
	{
		vm->cycle += 1;
		check_opt(vm);
		if (last_check == vm->cycle - vm->cycle_to_die)
		{
			checks(vm);
			purge_process(vm, last_check);
			last_check = vm->cycle;
		}
		if (vm->flag & verbose)
			printf("It is now cycle %ld\n", vm->cycle);
	}
	print_winner(vm);
	printf("%lu\n", vm->cycle);
}

int		main(int ac, char **av)
{
	t_vm	vm;
	t_arg	arg;

	arg.ac = ac;
	arg.av = av;
	arg.i = 0;
	if (ac == 1)
		usage(av[0]);
	memset(&vm, 0, sizeof(t_vm));
	set_flag(&vm, &arg);
	if ((vm.champ = init_champ__()) == NULL)
		p_error();
	vm.nb_player = set_champ(vm.champ, &arg);
	set_map(&vm);
	play(&vm);
	print_map(vm.map);
	return (0);
}
