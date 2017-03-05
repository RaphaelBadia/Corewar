/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:04:04 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 18:29:31 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*dst_ptr;
	const char	*src_ptr;
	size_t		free_space;
	size_t		dest_used_bytes;

	dst_ptr = dst;
	src_ptr = src;
	free_space = size;
	while (free_space-- > 0 && *dst_ptr != '\0')
		dst_ptr++;
	dest_used_bytes = dst_ptr - dst;
	free_space = size - dest_used_bytes;
	if (free_space == 0)
		return (dest_used_bytes + ft_strlen(src));
	while (*src_ptr != '\0')
	{
		if (free_space > 1)
		{
			*dst_ptr++ = *src_ptr;
			free_space--;
		}
		src_ptr++;
	}
	*dst_ptr = '\0';
	return (dest_used_bytes + (src_ptr - src));
}
