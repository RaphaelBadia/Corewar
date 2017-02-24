/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:36:22 by jye               #+#    #+#             */
/*   Updated: 2016/11/08 18:39:25 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*cur;
	t_list	*next;

	if (*alst == NULL)
		return ;
	cur = *alst;
	while (cur != NULL)
	{
		next = cur->next;
		del(cur->content, cur->content_size);
		free(cur);
		cur = next;
	}
	*alst = NULL;
}
