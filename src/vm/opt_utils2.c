/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:18:26 by jye               #+#    #+#             */
/*   Updated: 2017/03/18 19:12:07 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>
#include <errno.h>
#include <unistd.h>
#include <vm.h>

unsigned int		nskip(unsigned char byte_code, unsigned char octal_code)
{
	int				i;
	unsigned int	skip;
	unsigned char	octal[3];

	i = 0;
	skip = 2;
	octal[0] = octal_code >> 6;
	octal[1] = (octal_code >> 4) & 3;
	octal[2] = (octal_code >> 2) & 3;
	while (i < g_op_tab[byte_code].argc)
	{
		if (octal[i] == DIR_CODE)
		{
			if (g_op_tab[byte_code].label_size)
				skip += 2;
			else
				skip += 4;
		}
		else if (octal[i] == REG_CODE)
			skip += 1;
		else if (octal[i] == IND_CODE)
			skip += 2;
		++i;
	}
	return (skip);
}

void				checks(t_vm *vm)
{
	unsigned int i;

	i = 0;
	if (vm->cycle == 0)
		return ;
	if (vm->live > 20 && !(vm->checks = 0))
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->flag & verbose)
			ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
	}
	else if (vm->checks == 9 && !(vm->checks = 0))
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->flag & verbose)
			ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
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
