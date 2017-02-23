/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:44:25 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/23 18:38:28 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "op.h"
#include <ft_printf.h>

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
	ft_addlabel(&data->knowns, label_name, data->buff_index, 0);
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

int			get_label_to_find(t_asm *data, char *line, char *op_buff, int *op_i)
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
	if (!(fill_label(label_name, data, op_buff, op_i)))
	{
		ft_addlabel(&data->to_fill, label_name, data->buff_index + *op_i, data->buff_index);
		return (0);
	}
	return (1);
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
			if (!get_label_to_find(data, arg_i + 2, op_buff, op_i))
			{
				ft_memcpy(op_buff + *op_i, "\0\0\0\0", dir_size);
				*op_i += dir_size;
			}
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
	fill_label_to_fill(data);
}
