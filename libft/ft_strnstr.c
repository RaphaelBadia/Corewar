/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:51:31 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:10:34 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int found_last_char_pos;

	found_last_char_pos = (ft_strstr(s1, s2) - s1) + ft_strlen(s2);
	if (found_last_char_pos > (int)n)
		return (NULL);
	return (ft_strstr(s1, s2));
}
