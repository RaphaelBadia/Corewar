/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 16:30:27 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/27 16:31:11 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <op.h>

void		free_lst(t_label *lst)
{
	t_label		*tmp;
	t_label		*tmp_next;

	tmp = lst;
	while (tmp)
	{
		tmp_next = tmp->next;
		free(tmp->label_name);
		free(tmp);
		tmp = tmp_next;
	}
}
