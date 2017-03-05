/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:54:52 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/12 10:54:36 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dest, const void *src, size_t n)
{
	t_byte			*dest_ptr;
	const t_byte	*src_ptr;
	size_t			i;

	dest_ptr = dest;
	src_ptr = src;
	if (n == 0)
		return (dest);
	i = (dest_ptr < src_ptr) ? 0 : n - 1;
	while (n > 0)
	{
		dest_ptr[i] = src_ptr[i];
		i = (dest_ptr < src_ptr) ? i + 1 : i - 1;
		n--;
	}
	return (dest_ptr);
}
