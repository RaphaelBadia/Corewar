/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:11:13 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/27 18:11:14 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <stdlib.h>

void		op_st(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x03;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 2)
		ft_exit_err("st must have 2 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_IND | T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
	ft_arrfree(args);
}
