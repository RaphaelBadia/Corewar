/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:40:31 by jye               #+#    #+#             */
/*   Updated: 2016/11/11 19:53:20 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*fresh;

	if ((fresh = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	if (content == NULL)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
		fresh->next = NULL;
	}
	else
	{
		if ((fresh->content = malloc(content_size)) == NULL)
		{
			free(fresh);
			return (NULL);
		}
		else
		{
			ft_memcpy(fresh->content, content, content_size);
			fresh->content_size = content_size;
			fresh->next = NULL;
		}
	}
	return (fresh);
}
