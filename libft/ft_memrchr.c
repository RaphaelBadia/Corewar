/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 16:36:15 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 17:47:28 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrchr(const void *s, int c, size_t n)
{
	const t_byte	*ptr;

	if (PROTECT_PARAMS && s == NULL)
		return (NULL);
	ptr = s;
	while (n > 0 && ptr[n - 1] != (t_byte)c)
		n--;
	if (n > 0)
		return ((void *)&ptr[n - 1]);
	return (NULL);
}
