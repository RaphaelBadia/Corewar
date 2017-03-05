/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_noalloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:11:20 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/03 15:12:25 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list		*ft_lstnew_noalloc(void const *content, size_t content_size)
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
	alst->content = (void *)content;
	alst->content_size = content_size;
	return (alst);
}
