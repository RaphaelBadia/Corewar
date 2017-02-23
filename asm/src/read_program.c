/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:44:25 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/23 17:29:40 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "op.h"
#include <ft_printf.h>

void		ft_addlabel(t_label **lst, char *name, int index)
{
	t_label	*new;

	if (!(new = malloc(sizeof(t_label))))
		ft_exit_err("malloc error", NULL);
	new->label_name = name;
	new->index = index;
	new->next = *lst;
	*lst = new;
}

void		display_labels(t_label *lst)
{
	ft_printf("Displaying a list:\n");
	while (lst)
	{
		ft_printf("%s was defined at index %d\n", lst->label_name, lst->index);
		lst = lst->next;
	}
}

char		*get_label(t_asm *data, char *line)
{
	int		i;
	int		label_size;
	char	*label_name;

	i = 0;
	while (is_one_of(line[i], " \t"))
		i++;
	label_size = 0;
	while (is_one_of(line[i + label_size], LABEL_CHARS))
		label_size++;
	if (line[i + label_size] != ':')
		return (line + i);
	label_name = ft_strndup(line + i, (size_t)label_size);
	ft_addlabel(&data->knowns, label_name, data->buff_index);
	return (line + i + label_size + 1);
}

void		check_type(unsigned char *op_buff, int args_i, int type, int type_argi, t_asm *data)
{
//	ft_printf("type = %d et argitype= %d\n", type, type_argi);
	if ((type_argi & type) == 0)
		ft_exit_err("bad type argument", data);
	if (type_argi == T_IND)
		*op_buff |= (T_INDB << (6 - 2 * args_i));
	else
		*op_buff |= (type_argi << (6 - 2 * args_i));
}

void		get_label_to_find(t_asm *data, char *line, int index)
{
	int		i;
	char	*label_name;

	i = 0;
	if (line[i] == '\0')
		ft_exit_err("no label name", data);
	while (line[i])
	{
		if (!is_one_of(line[i], LABEL_CHARS))
			ft_exit_err("wrong label chars", data);
		i++;
	}
	if (!(label_name = ft_strdup(line)))
		ft_exit_err("malloc", data);
	ft_addlabel(&data->to_fill, label_name, data->buff_index + index);
}

int			get_param(char *op_buff, int *op_i, char *arg_i, t_asm *data, int dir_size)
{
	int		reg;
	int		dir;

	if (arg_i[0] == 'r')
	{
		if (!ft_atoi_safe(arg_i + 1, &reg) || reg < 0 || reg > 16)
			ft_exit_err("reg must be like r<0-16>\n", data);
		ft_memcpy(op_buff + *op_i, &reg, 1);
		*op_i += 1;
		return (T_REG);
	}
	else if (arg_i[0] == '%')
	{
		if (arg_i[1] == ':')
		{
			get_label_to_find(data, arg_i + 2, *op_i);
			ft_memcpy(op_buff + *op_i, "\0\0\0\0", dir_size);
			*op_i += dir_size;
		}
		else
		{
			if (!ft_atoi_safe(arg_i + 1, &dir))
				ft_exit_err("%% must be followed only by nb or :label\n", data);
			if (dir_size == 2)
				dir <<= 16;
			dir = swap_bits(dir);
			ft_memcpy(op_buff + *op_i, &dir, dir_size);
			*op_i += dir_size;
		}
		return (T_DIR);
	}
	else
	{
		return (T_IND);
	}
}

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
	ft_printf("hi");
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
	ft_printf("hi");
	type_argi = get_param((char*)op_buff, &op_i, args[args_i], data, 2);
	check_type(&unused_octal, args_i, T_DIR, type_argi, data);
	args_i++;
	ft_cpy_buf(op_buff, data, op_i);
	(void)data;
}

void		get_instruction(t_asm *data, char *line)
{
	int		i;
	int		j;
	int		instruction_size;

	i = 0;
	j = 0;
	while (is_one_of(line[i], " \t"))
		i++;
	instruction_size = 0;
	while (!is_one_of(line[i + instruction_size], " \t"))
		instruction_size++;
	while (j < 16)
	{
		if (ft_strnequ(g_ops[j].name, line + i, instruction_size))
		{
			//ft_printf("\nwow i have to execute '%s'\n", g_ops[j].name);
			g_ops[j].op(data, splitrim(line + i + instruction_size, data));
		}
		j++;
	}
}

void		read_program(t_asm *data, int fd)
{
	int		ret;
	char	*line;
	char	*str;

	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!empty(line))
		{
			str = get_label(data, line);
			get_instruction(data, str);
		}
		free(line);
	}
	display_labels(data->knowns);
	display_labels(data->to_fill);
	ft_printf("\nDIST : %d\n", data->to_fill->next->index - data->begin_program);
	// 06 00 00 00
	// 00 00 00 06
	short diff = data->knowns->index - data->to_fill->index;
	ft_printf("diff: %#d, first: %hx, second: %hx\n", diff, diff >> 8 & 0xff, diff & 0xff);
	data->buffer[data->to_fill->index] = diff >> 8 & 0xff;
	data->buffer[data->to_fill->index + 1] = diff & 0xff;
	// le +1 doit etre fait en fonction de si ya un octal ou non.
}
