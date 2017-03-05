/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:19:53 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:13:06 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*last_char;

	i = 0;
	last_char = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			last_char = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		last_char = (char *)&s[i];
	if (last_char)
		return (last_char);
	return (NULL);
}
