/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:51:22 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 15:24:48 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (PROTECT_PARAMS && (s1 == NULL || s2 == NULL))
		return (0);
	i = 0;
	if (n == 0)
		return (1);
	while (s1[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return (s1[i] == s2[i]);
}
