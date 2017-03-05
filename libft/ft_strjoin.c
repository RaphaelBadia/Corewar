/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:06:23 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 15:26:50 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstr;

	if (PROTECT_PARAMS && (s1 == NULL || s2 == NULL))
		return (0);
	joinstr = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (joinstr == NULL)
		return (NULL);
	return (ft_strcat(ft_strcat(joinstr, s1), s2));
}
