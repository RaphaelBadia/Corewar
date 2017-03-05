/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:48:54 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 15:55:44 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	if (PROTECT_PARAMS && (alst == NULL || *alst == NULL || del == NULL))
		return ;
	while ((*alst) != NULL)
	{
		next = (*alst)->next;
		ft_lstdelone(alst, del);
		(*alst) = next;
	}
}
