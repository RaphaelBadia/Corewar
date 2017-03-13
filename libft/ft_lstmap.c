/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:47:09 by jye               #+#    #+#             */
/*   Updated: 2016/11/08 18:33:41 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *cur;
	t_list *ret;

	if (lst == NULL || !f)
		return (NULL);
	ret = f(lst);
	if ((new = ft_lstnew(ret->content, ret->content_size)) == NULL)
		return (NULL);
	lst = lst->next;
	cur = new;
	while (lst != NULL)
	{
		ret = f(lst);
		if ((cur->next = ft_lstnew(ret->content, ret->content_size)) == NULL)
			return (NULL);
		cur = cur->next;
		lst = lst->next;
	}
	return (new);
}
