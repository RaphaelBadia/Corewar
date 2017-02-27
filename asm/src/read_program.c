/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:44:25 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/27 18:14:57 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "op.h"
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
	while (line[i + instruction_size] != '\0' &&
	!is_one_of(line[i + instruction_size], " \t"))
		instruction_size++;
	if (instruction_size == 0)
		return ;
	data->column += i;
	while (j < 16)
	{
		if (ft_strnequ(g_ops[j].name, line + i, instruction_size))
		{
			g_ops[j].op(data, splitrim(line + i + instruction_size, data));
			return ;
		}
		j++;
	}
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
