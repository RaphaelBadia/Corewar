/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:14:52 by vcombey           #+#    #+#             */
/*   Updated: 2017/03/16 18:13:53 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <op.h>
#include <asm.h>
#include <ft_printf.h>

static int	is_nb(char c)
{
	return (ft_isdigit(c) || c == '-');
}

int			get_param_dir(t_instruction *ins, char *param, t_asm *data,
		int dir_size)
{
	int		dir;

	if (param[1] == ':')
	{
		data->column += 2;
		if (!get_label_to_find(data, param + 2, ins->op_buff, &(ins->op_i)))
		{
			ft_memcpy(ins->op_buff + ins->op_i, "\0\0\0\0", dir_size);
			ins->op_i += dir_size;
		}
	}
	else
	{
		data->column += 1;
		if (!ft_atoi_safe(param + 1, &dir) || !is_nb(*(param + 1)))
			ft_exit_err("%% must be followed by a number or a :label", data);
		if (dir_size == 2)
			dir <<= 16;
		dir = swap_bits(dir);
		ft_memcpy(ins->op_buff + ins->op_i, &dir, dir_size);
		ins->op_i += dir_size;
	}
	return (T_DIR);
}

int			get_param_indir(t_instruction *ins, char *param, t_asm *data)
{
	int		dir;

	data->actual_label_size = 2;
	if (param[0] == ':')
	{
		data->column += 1;
		if (!get_label_to_find(data, param + 1, ins->op_buff, &(ins->op_i)))
		{
			ft_memcpy(ins->op_buff + ins->op_i, "\0\0\0\0", 2);
			ins->op_i += 2;
		}
	}
	else
	{
		if (!ft_atoi_safe(param, &dir))
			ft_exit_err("indir must be a nb or a :label\n", data);
		dir <<= 16;
		dir = swap_bits(dir);
		ft_memcpy(ins->op_buff + ins->op_i, &dir, 2);
		ins->op_i += 2;
	}
	return (T_IND);
}

int			get_param(t_instruction *ins, char *param, t_asm *data,
		int dir_size)
{
	int		reg;

	if (param[0] == 'r')
	{
		data->column += 1;
		if (!ft_atoi_safe(param + 1, &reg) || reg < 1 || reg > 16)
			ft_exit_err("reg must be like r<1-16>", data);
		ft_memcpy(ins->op_buff + ins->op_i, &reg, 1);
		ins->op_i += 1;
		return (T_REG);
	}
	else if (param[0] == '%')
		return (get_param_dir(ins, param, data, dir_size));
	else
		return (get_param_indir(ins, param, data));
}
