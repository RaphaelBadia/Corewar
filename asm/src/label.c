/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 18:04:32 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/23 18:44:32 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "op.h"
#include "ft_printf.h"

static t_label	*ft_find_label_in_lst(char *name, t_label *lst)
{
	t_label		*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strequ(tmp->label_name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void			display_to_fill_list(t_label *lst)
{
	ft_printf("labels to fill:\n");
	while (lst)
	{
		ft_printf("%s is needed at %d\n", lst->label_name, lst->index);
		lst = lst->next;
	}
}

int				fill_label(char *name, t_asm *data, char *op_buff, int *op_i)
{
	t_label		*find;

	if ((find = ft_find_label_in_lst(name, data->knowns)) == NULL)
		return (0);
	display_labels(data->knowns);
	ft_printf("\n");
	display_to_fill_list(data->to_fill);
	short diff = find->index - data->buff_index;
	ft_printf("diff: %#d, first: %hx, second: %hx\n", diff, diff >> 8 & 0xff, diff & 0xff);
	op_buff[*op_i] = diff >> 8 & 0xff;
	op_buff[*op_i + 1] = diff & 0xff;
	*op_i += 2;
	// le +1 doit etre fait en fonction de si ya un octal ou non.
	return (1);
}

int				fill_label_2(char *name, t_label *to_fill, t_asm *data)
{
	t_label		*know;

	if ((know = ft_find_label_in_lst(name, data->knowns)) == NULL)
		return (0);
	display_labels(data->knowns);
	ft_printf("\n");
	//display_to_fill_list(data->to_fill);
	short diff = know->index - to_fill->index_op;
	ft_printf("diff: %#d, first: %hx, second: %hx\n", diff, diff >> 8 & 0xff, diff & 0xff);
	data->buffer[to_fill->index] = diff >> 8 & 0xff;
	data->buffer[to_fill->index + 1] = diff & 0xff;
	// le +1 doit etre fait en fonction de si ya un octal ou non.
	return (1);
}

void			fill_label_to_fill(t_asm *data)
{
	t_label		*tmp;

	tmp = data->to_fill;
	while (tmp)
	{
		if (!(fill_label_2(tmp->label_name, tmp, data)))
			ft_exit_err("label not found", data);
		tmp = tmp->next;
	}
}

void			ft_addlabel(t_label **lst, char *name, int index, int index_op)
{
	t_label	*new;

	if (!(new = malloc(sizeof(t_label))))
		ft_exit_err("malloc error", NULL);
	new->label_name = name;
	new->index = index;
	new->index_op = index_op;
	new->next = *lst;
	*lst = new;
}

void			display_labels(t_label *lst)
{
	ft_printf("Displaying a list:\n");
	while (lst)
	{
		ft_printf("%s was defined at index %d\n", lst->label_name, lst->index);
		lst = lst->next;
	}
}
