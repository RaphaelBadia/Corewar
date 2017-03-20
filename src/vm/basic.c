/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 18:24:06 by jye               #+#    #+#             */
/*   Updated: 2017/03/20 17:21:37 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	play__(t_vm *vm)
{
	unsigned long	last_check;

	last_check = 0;
	introduce(vm);
	while (vm->process)
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
			printf("It is now cycle %ld\n", vm->cycle);
	}
	print_winner(vm);
}

void		introduce(t_vm *vm)
{
	unsigned int	i;

	i = 0;
	printf("Introducing constestants...\n");
	while (i < vm->nb_player)
	{
		printf(" * Player %d ID %d \"%s\" (\"%s\") weighting %u bytes\n", i + 1,
				vm->champ[i].id_player,
				vm->champ[i].name,
				vm->champ[i].comment,
				vm->champ[i].size);
		++i;
	}
}

void		print_winner(t_vm *vm)
{
	int		i;
	t_champ	*win;

	win = &vm->champ[0];
	i = 0;
	while (i < vm->nb_player)
	{
		if (win->last_live < vm->champ[i].last_live)
			win = &vm->champ[i];
		++i;
	}
	printf("Contestant %d, \"%s\", has won !\n", win->id_player, win->name);
}

void		play(t_vm *vm)
{
	if (vm->flag & visual)
		init_ncurses(vm);
	set_map(vm);
	vm->id_track = 1;
	vm->process = init_process(vm);
	vm->cycle_to_die = CYCLE_TO_DIE;
	if (vm->flag & dump)
		dump_play(vm);
	else if (vm->flag & stop)
		stop_play(vm);
	else if (vm->flag & visual)
		visual_play(vm);
	else
		play__(vm);
}
