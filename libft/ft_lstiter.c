/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:12:22 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 15:59:09 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list	*tmp;

	if (PROTECT_PARAMS && (lst == NULL || f == NULL))
		return ;
	while (lst != NULL)
	{
		tmp = lst->next;
		f(lst);
		lst = tmp;
	}
}
