/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:40:33 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/20 19:15:53 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <graphic.h>

void	live(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	unsigned int	id_player;
	unsigned int	i;

	pc = process->pc;
	id_player = get_dir(vm, pc + 1, 0);
	i = 0;
	if (vm->flag & verbose)
		ft_printf("P %4d | live %d\n", process->id, id_player);
	while (i < vm->nb_player)
	{
		if (vm->champ[i].id_player == id_player)
		{
			if (vm->flag & verbose)
				ft_printf("Player %d (%s) is said to be alive\n",
				-vm->champ[i].id_player, vm->champ[i].name);
			vm->champ[i].last_live = vm->cycle;
			vm->champ[i].live += 1;
			refresh_map(vm, process->pc, 5, process->id_player);
		}
		++i;
	}
	vm->live += 1;
	process->last_live = vm->cycle;
	process->pc += 5;
}
