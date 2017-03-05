/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:40:40 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/13 16:03:31 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(const t_list *lst, void (*fdisplay)(const void *, size_t))
{
	if (PROTECT_PARAMS && fdisplay == NULL)
		return ;
	while (lst != NULL)
	{
		fdisplay(lst->content, lst->content_size);
		lst = lst->next;
	}
}
