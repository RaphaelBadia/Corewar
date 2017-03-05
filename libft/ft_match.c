/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/10 18:34:25 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 18:57:54 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_match(const char *s1, const char *s2)
{
	if (PROTECT_PARAMS && (s1 == NULL || s2 == NULL))
		return (0);
	if ((*s1 == '\0') && (*s2 == '\0'))
		return (1);
	if (*s2 == '*')
	{
		if (*s1 != '\0')
			return (ft_match(s1, s2 + 1) || ft_match(s1 + 1, s2));
		return (ft_match(s1, s2 + 1));
	}
	if (*s1 == *s2)
		return (ft_match(s1 + 1, s2 + 1));
	return (0);
}
