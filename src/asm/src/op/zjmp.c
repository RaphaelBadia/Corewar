/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:11:28 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/27 18:12:08 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <stdlib.h>

void		op_zjmp(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.args_i = 0;
	ins.op_buff[0] = 0x09;
	ins.op_i = 1;
	if (ft_strstrlen(args) != 1)
		ft_exit_err("zjump must have 1 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(NULL, T_DIR, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
	ft_arrfree(args);
}
