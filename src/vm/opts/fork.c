/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 15:44:53 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/20 18:57:22 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <vm.h>
#include <ft_printf.h>
#include <libft.h>

void	frk(t_vm *vm, t_process *process)
{
	t_process		*new_p;
	unsigned int	pc;
	int				bool_;
	short			target;
	unsigned char	byte_code;

	if (!(new_p = malloc(sizeof(t_process))))
		p_error();
	pc = process->pc;
	target = get_dir(vm, pc + 1, 1);
	if (vm->flag & verbose)
		ft_printf("P %4d | fork %hd (%d)\n",
		process->id, target, pc + (target % IDX_MOD));
	ft_memcpy(new_p, process, sizeof(t_process));
	new_p->pc += (target % IDX_MOD);
	byte_code = vm->map[PTR(new_p->pc)];
	vm->nb_process += 1;
	bool_ = (byte_code > 0 && byte_code <= 16);
	new_p->op_code = bool_ ? byte_code : 0;
	new_p->exec_cycle = bool_ ? g_op_tab[byte_code].cycles + vm->cycle : 0;
	new_p->id = vm->id_track++;
	push_lst__(&vm->process, new_p);
	process->pc += 3;
}
