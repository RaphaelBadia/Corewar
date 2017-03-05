/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:13:09 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 17:30:59 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newlst;

	if (PROTECT_PARAMS && (lst == NULL || f == NULL))
		return (NULL);
	newlst = (t_list *)malloc(sizeof(f(lst)));
	if (newlst == NULL)
		return (NULL);
	newlst = f(lst);
	newlst->next = ft_lstmap(lst->next, f);
	return (newlst);
}
