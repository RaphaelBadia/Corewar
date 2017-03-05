/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:53:50 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/04 14:16:54 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	char	*tmp;

	tmp = dest + ft_strlen(dest);
	i = 0;
	while (src[i] && i < n)
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (dest);
}
