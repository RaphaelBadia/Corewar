/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:45:24 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/13 15:52:10 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <vm.h>

void	lldi(t_vm *vm, t_process *process)
{
	unsigned int	pc[2];
	int				i;
	int				r[3];
	unsigned char	octal[2];

	pc[0] = process->pc;
	pc[1] = process->pc + 2;
	i = 0;
	octal[0] = vm->map[PTR(pc[0] + 1)] >> 6;
	octal[1] = (vm->map[PTR(pc[0] + 1)] >> 4) & 3;
	while (i < 2)
	{
		r[i] = get_param(vm, process, pc, (int[3]){octal[i], 1, 1});
		++i;
	}
	r[2] = vm->map[PTR(pc[1])];
	if (vm->flag & verbose)
		ft_printf("P %4d | lldi %d %d r%d\n", process->id, r[0], r[1], r[2]);
	process->r[r[2] - 1] = get_dir(vm, pc[0] + ((r[0] + r[1])), 0);
	process->pc = pc[1] + 1;
}
