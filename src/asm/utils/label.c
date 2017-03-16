/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 20:21:34 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/16 19:33:38 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <op.h>
#include <asm.h>

void			ft_addlabel(t_label **lst, char *name, int index, int index_op)
{
	t_label	*new;

	if (!(new = malloc(sizeof(t_label))))
		ft_exit_err("malloc error", NULL);
	new->label_name = name;
	new->index = index;
	new->index_op = index_op;
	new->next = *lst;
	new->column = -1;
	new->line = -1;
	*lst = new;
}

void			ft_addlabelline(t_label *label, t_asm *data)
{
	label->line = data->line;
	label->column = data->column;
	label->label_size = data->actual_label_size;
	if (data->is_indir)
		label->label_size = 2;
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

t_label			*ft_find_label_in_lst(char *name, t_label *lst)
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

void			display_to_fill_list(t_label *lst)
{
	ft_printf("labels to fill:\n");
	while (lst)
	{
		ft_printf("%s is needed at %d\n", lst->label_name, lst->index);
		lst = lst->next;
	}
}
