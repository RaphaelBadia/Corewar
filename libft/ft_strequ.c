/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:03:07 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 15:25:05 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	if (PROTECT_PARAMS && (s1 == NULL || s2 == NULL))
	{
		if (s1 == s2)
			return (1);
		return (0);
	}
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] == s2[i]);
}
