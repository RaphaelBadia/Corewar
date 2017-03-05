/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:48:37 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/12 10:59:13 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	t_byte			*dest_ptr;
	const t_byte	*src_ptr;
	size_t			i;

	i = 0;
	dest_ptr = dest;
	src_ptr = src;
	while (n > 0 && src_ptr[i] != (t_byte)c)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
		n--;
	}
	if (n > 0)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
		return ((void *)&dest_ptr[i]);
	}
	return (NULL);
}
