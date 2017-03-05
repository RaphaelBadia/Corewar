/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:01:21 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/12 10:59:32 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	t_byte			*dest_ptr;
	const t_byte	*src_ptr;
	size_t			i;

	i = 0;
	dest_ptr = dest;
	src_ptr = src;
	while (n > 0)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
		n--;
	}
	return (dest_ptr);
}
