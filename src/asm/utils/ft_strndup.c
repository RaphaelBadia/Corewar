/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:10:58 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/22 19:00:54 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char		*ft_strndup(const char *s, size_t n)
{
	char	*dst;

	if (s == NULL)
		return (NULL);
	dst = (char *)malloc((n + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	ft_strncpy(dst, s, n);
	dst[n] = 0;
	return (dst);
}
