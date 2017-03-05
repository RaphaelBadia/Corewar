/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 10:14:05 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 17:33:28 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*alst;

	alst = (t_list *)malloc(sizeof(t_list));
	if (alst == NULL)
		return (NULL);
	alst->next = NULL;
	if (content == NULL)
	{
		alst->content = NULL;
		alst->content_size = 0;
		return (alst);
	}
	alst->content = (void *)malloc(content_size);
	if (alst->content == NULL)
		return (NULL);
	alst->content_size = content_size;
	ft_memcpy(alst->content, content, content_size);
	return (alst);
}
