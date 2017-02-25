/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:03:34 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/25 21:21:10 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "ft_printf.h"
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
}

void		op_ld(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x02;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 2)
		ft_exit_err("ld must have 2 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

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
}

void		op_add(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x04;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("add must have 3 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_sub(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x05;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("sub must have 3 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_and(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x06;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("and must have 3 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_or(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x07;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("or must have 3 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_xor(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x08;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("xor must have 3 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

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
}

void		op_ldi(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x0a;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("ldi must have 3 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG | T_DIR, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_sti(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x0b;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("sti must have 3 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_DIR | T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_fork(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.args_i = 0;
	ins.op_buff[0] = 0x0c;
	ins.op_i = 1;
	if (ft_strstrlen(args) != 1)
		ft_exit_err("fork must have 1 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(NULL, T_DIR, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_lld(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x0d;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 2)
		ft_exit_err("lld must have 2 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 4);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_lldi(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.op_i = 2;
	ins.args_i = 0;
	ins.op_buff[0] = 0x0e;
	ins.op_buff[1] = 0;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("sti must have 3 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG | T_DIR | T_IND, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG | T_DIR, type_argi, data);
	ins.args_i++;
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(&ins, T_REG, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

void		op_lfork(t_asm *data, char **args)
{
	t_instruction	ins;
	int				type_argi;

	ins.args_i = 0;
	ins.op_buff[0] = 0x0f;
	ins.op_i = 1;
	if (ft_strstrlen(args) != 1)
		ft_exit_err("lfork must have 1 params", data);
	type_argi = get_param(&ins, args[ins.args_i], data, 2);
	check_type(NULL, T_DIR, type_argi, data);
	ft_cpy_buf((unsigned char*)ins.op_buff, data, ins.op_i);
}

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
}

void		op_nothing(t_asm *data, char **args)
{
	(void)data;
	(void)args;
	ft_printf("im not coded yet\n");
	exit(1);
}
