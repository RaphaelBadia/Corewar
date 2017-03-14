/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 17:45:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/27 18:10:53 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdlib.h>

void		op_live(t_asm *data, char **args)
{
	int				type_argi;
	t_instruction	ins;

	ins.op_i = 1;
	ins.args_i = 0;
	ins.op_buff[0] = 0x01;
	if (ft_strstrlen(args) != 1)
		ft_exit_err("live must have 1 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(NULL, T_DIR, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
	ft_arrfree(args);
}
