/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:42:02 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/20 18:58:10 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vm.h>
#include <ft_printf.h>

void	and(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	int				i;
	unsigned int	r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	octal[0] = vm->map[PTR(pc[0] + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	i = 0;
	while (i < 2)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i], 0, 1});
		++i;
	}
	r[2] = vm->map[PTR(pc[1])];
	if (vm->flag & verbose)
		ft_printf("P %4d | and %d %d r%d\n", process->id, r[0], r[1], r[2]);
	if ((process->r[r[2] - 1] = r[0] & r[1]) == 0)
		process->carry = 1;
	else
		process->carry = 0;
	process->pc = pc[1] + 1;
}
