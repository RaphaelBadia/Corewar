/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:04:32 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/15 11:55:29 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <op.h>
#include <asm.h>
#include "ft_printf.h"

int				fill_label(char *name, t_asm *data, char *op_buff, int *op_i)
{
	t_label		*find;
	short		diff;

	if ((find = ft_find_label_in_lst(name, data->knowns)) == NULL)
		return (0);
	diff = find->index - data->buff_index;
	if (data->actual_label_size == 2)
	{
		op_buff[*op_i] = diff >> 8 & 0xff;
		op_buff[*op_i + 1] = diff & 0xff;
		*op_i += 2;
	}
	if (data->actual_label_size == 4)
	{
		op_buff[*op_i] = diff >> 24 & 0xff;
		op_buff[*op_i + 1] = diff >> 16 & 0xff;
		op_buff[*op_i + 2] = diff >> 8 & 0xff;
		op_buff[*op_i + 3] = diff & 0xff;
		*op_i += 4;
	}
	free(name);
	return (1);
}

int				fill_label_2(char *name, t_label *to_fill, t_asm *data)
{
	t_label		*know;
	short		diff;

	if ((know = ft_find_label_in_lst(name, data->knowns)) == NULL)
		return (0);
	diff = know->index - to_fill->index_op;
	data->buffer[to_fill->index] = diff >> 8 & 0xff;
	data->buffer[to_fill->index + 1] = diff & 0xff;
	return (1);
}

void			fill_label_to_fill(t_asm *data)
{
	t_label		*tmp;

	tmp = data->to_fill;
	while (tmp)
	{
		if (!(fill_label_2(tmp->label_name, tmp, data)))
		{
			data->line = tmp->line;
			data->column = tmp->column;
			ft_exit_err("label not found", data);
		}
		tmp = tmp->next;
	}
}

char			*get_label(t_asm *data, char *line)
{
	int		i;
	int		label_size;
	char	*label_name;

	i = 0;
	while (is_one_of(line[i], " \t"))
		i++;
	data->column += i;
	label_size = 0;
	while (is_one_of(line[i + label_size], LABEL_CHARS))
		label_size++;
	if (line[i + label_size] != ':')
		return (line + i);
	label_name = ft_strndup(line + i, (size_t)label_size);
	ft_addlabel(&data->knowns, label_name, data->buff_index, 0);
	data->column += label_size + 1;
	return (line + i + label_size + 1);
}

int				get_label_to_find(t_asm *data, char *line, char *op_buff,
	int *op_i)
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
		data->column++;
	}
	if (!(label_name = ft_strdup(line)))
		ft_exit_err("malloc", data);
	if (!(fill_label(label_name, data, op_buff, op_i)))
	{
		ft_addlabel(&data->to_fill, label_name, data->buff_index + *op_i,
			data->buff_index);
		ft_addlabelline(data->to_fill, data);
		return (0);
	}
	return (1);
}
