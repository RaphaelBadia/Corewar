/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:09:52 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/27 18:12:15 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <stdlib.h>

void		op_aff(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x10;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 1)
		ft_exit_err("aff must have 1 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
	ft_arrfree(args);
}
