/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:44:25 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/15 11:55:10 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <op.h>
#include <asm.h>
#include <ft_printf.h>

void		check_type(t_instruction *ins, int type, int type_argi, t_asm *data)
{
	if ((type_argi & type) == 0)
		ft_exit_err("bad type argument", data);
	if ((ins != NULL) && type_argi == T_IND)
		ins->op_buff[1] |= (T_INDB << (6 - 2 * ins->args_i));
	else if (ins != NULL)
		ins->op_buff[1] |= (type_argi << (6 - 2 * ins->args_i));
}

int			exec_opt(t_asm *data, char *line, int instruction_size)
{
	int			j;
	static void	(*f[])() = {NULL, &op_live, &op_ld, &op_st, &op_add, &op_sub,
		&op_and, &op_or, &op_xor, &op_zjmp, &op_ldi, &op_sti, &op_fork,
		&op_lld, &op_lldi, &op_lfork, &op_aff};

	j = 1;
	while (j < 17)
	{
		if (ft_strnequ(g_op_tab[j].name, line, instruction_size))
		{
			data->actual_label_size = g_op_tab[j].label_size;
			data->column += ft_strlen(g_op_tab[j].name);
			f[j](data, splitrim(line + instruction_size, data));
			return (1);
		}
		j++;
	}
	return (0);
}

void		get_instruction(t_asm *data, char *line)
{
	int		i;
	int		instruction_size;

	i = 0;
	while (is_one_of(line[i], " \t"))
		i++;
	instruction_size = 0;
	while (line[i + instruction_size] != '\0' &&
	!is_one_of(line[i + instruction_size], " \t"))
		instruction_size++;
	if (instruction_size == 0)
		return ;
	data->column += i;
	if (!exec_opt(data, line + i, instruction_size))
		ft_exit_err("unkown command", data);
}

void		read_program(t_asm *data, int fd)
{
	int		ret;
	char	*line;
	char	*str;

	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!empty(remove_comment(line)))
		{
			str = get_label(data, line);
			get_instruction(data, str);
		}
		free(line);
		data->line++;
		data->column = 1;
	}
	fill_label_to_fill(data);
}
