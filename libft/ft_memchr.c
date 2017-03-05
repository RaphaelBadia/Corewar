/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:34:02 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/12 10:59:22 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const t_byte	*ptr;
	size_t			i;

	ptr = s;
	i = 0;
	while (n > 0 && ptr[i] != (t_byte)c)
	{
		i++;
		n--;
	}
	if (n > 0)
		return ((void *)&ptr[i]);
	return (NULL);
}
