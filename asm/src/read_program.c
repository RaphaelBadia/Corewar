/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:44:25 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/22 20:49:54 by rbadia           ###   ########.fr       */
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

void		check_type(char *op_buff, int type_argi, int args_i, int type)
{
	if ((arg_type & type) == 0)
		ft_exit_err("bad type argument", data);
	*op_buff |= (type << args_i);
}

int			get_param(char *op_buff, int *op_i, char *arg_i)
{
	int argi_type;

	if (arg_i[0] == 'r')
		dsds;
}

void		op_sti(t_asm *data, char **args)
{
	unsigned char	op_buff[7];
	int				op_i;
	int				args_i;
	int				type;

	op_i = 0;
	op_buff[0] = 0x0b;
	if (ft_strstrlen(args) != 3)
		ft_exit_err("sti must have 3 params", NULL);
	type = get_param(op_buff, &op_i, args[args_i]);
	check_type(op_buff + 1, args_i, T_REGB, type);
	args_i++;
	type = get_param(op_buff, &op_i, args[args_i]);
	check_type(op_buff + 1, args_i, T_REGB | T_DIRB | T_INDB, type);
	args_i++;
	type = get_param(op_buff, &op_i, args[args_i]);
	check_type(op_buff + 1, args_i, T_DIRB | T_REGB, type);
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
			ft_printf("\nwow i have to execute '%s'\n", g_ops[j].name);
			op_sti(data, splitrim(line + i + instruction_size, data));
			exit(1);
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
}
