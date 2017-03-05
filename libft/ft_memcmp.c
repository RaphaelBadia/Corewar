/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:43:29 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 17:42:08 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *b1, const void *b2, size_t len)
{
	t_byte *byte1;
	t_byte *byte2;

	byte1 = (t_byte *)b1;
	byte2 = (t_byte *)b2;
	while (len--)
	{
		if (*byte1 != *byte2)
			return (*byte1 - *byte2);
		byte1++;
		byte2++;
	}
	return (0);
}
