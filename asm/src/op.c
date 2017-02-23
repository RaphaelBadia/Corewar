/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:03:34 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/23 18:15:54 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"

void		op_nothing(t_asm *data, char **args)
{
	(void)data;
	(void)args;
	ft_printf("\nWell, i'm useless.\n");
}

void		op_sti(t_asm *data, char **args)
{
	unsigned char	op_buff[7];
	int				op_i;
	int				args_i;
	int				type_argi;

	op_i = 2;
	args_i = 0;
	op_buff[0] = 0x0b;
	op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("sti must have 3 params", data);
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 2);
	check_type(op_buff + 1, args_i, T_REG, type_argi, data);
	args_i++;
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 2);
	check_type(op_buff + 1, args_i, T_REG | T_DIR | T_IND, type_argi, data);
	args_i++;
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 2);
	check_type(op_buff + 1, args_i, T_DIR | T_REG, type_argi, data);
	args_i++;
	ft_cpy_buf(op_buff, data, op_i);
	(void)data;
}

void		op_and(t_asm *data, char **args)
{
	unsigned char	op_buff[9];
	int				op_i;
	int				args_i;
	int				type_argi;

	op_i = 2;
	args_i = 0;
	op_buff[0] = 0x06;
	op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("and must have 3 params", data);
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 4);
	check_type(op_buff + 1, args_i, T_REG | T_DIR | T_IND, type_argi, data);
	args_i++;
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 4);
	check_type(op_buff + 1, args_i, T_REG | T_DIR | T_IND, type_argi, data);
	args_i++;
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 4);
	check_type(op_buff + 1, args_i, T_REG, type_argi, data);
	args_i++;
	ft_cpy_buf(op_buff, data, op_i);
	(void)data;
}

void		op_live(t_asm *data, char **args)
{
	unsigned char	op_buff[5];
	unsigned char	unused_octal;
	int				op_i;
	int				args_i;
	int				type_argi;

	args_i = 0;
	op_buff[0] = 0x01;
	op_i = 1;
	if (ft_strstrlen(args) != 1)
		ft_exit_err("live must have 1 params", data);
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 4);
	check_type(&unused_octal, args_i, T_DIR, type_argi, data);
	args_i++;
	ft_cpy_buf(op_buff, data, op_i);
	(void)data;
}

void		op_zjmp(t_asm *data, char **args)
{
	unsigned char	op_buff[5];
	unsigned char	unused_octal;
	int				op_i;
	int				args_i;
	int				type_argi;

	args_i = 0;
	op_buff[0] = 0x09;
	op_i = 1;
	if (ft_strstrlen(args) != 1)
		ft_exit_err("zjump must have 1 params", data);
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 2);
	check_type(&unused_octal, args_i, T_DIR, type_argi, data);
	args_i++;
	ft_cpy_buf(op_buff, data, op_i);
	(void)data;
}
