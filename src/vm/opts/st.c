/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:41:11 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/20 19:15:53 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <graphic.h>

void	st(t_vm *vm, t_process *process)
{
	unsigned int	pc;
	unsigned int	octal;
	unsigned int	reg;
	unsigned int	offset;
	int				param;

	pc = process->pc;
	octal = (vm->map[PTR(pc + 1)] >> 4) & 3;
	reg = vm->map[PTR(pc + 2)];
	if (vm->flag & verbose)
		ft_printf("P %4d | st r%d ", process->id, reg);
	offset = octal == REG_CODE ? 4 : 5;
	reg = process->r[reg - 1];
	if (octal == REG_CODE && (param = vm->map[PTR(pc + 3)]))
		process->r[param - 1] = reg;
	else
	{
		param = (short)get_dir(vm, pc + 3, 1);
		st_param(vm, pc + (param % IDX_MOD), reg);
		refresh_map(vm, PTR(pc + (param % IDX_MOD)), 4, process->id_player);
	}
	if (vm->flag & verbose)
		ft_printf("%d\n", param);
	process->pc += offset;
}
