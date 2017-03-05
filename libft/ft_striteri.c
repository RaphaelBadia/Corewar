/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:46:27 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 18:20:58 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	if (PROTECT_PARAMS && (s == NULL || f == NULL))
		return ;
	i = 0;
	while (s[i])
	{
		f((unsigned int)i, (s + i));
		i++;
	}
}
