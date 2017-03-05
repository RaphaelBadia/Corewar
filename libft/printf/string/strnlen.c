/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:36:10 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/30 17:37:04 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t					strnlen_(const char *s, size_t n)
{
	register const char *str;

	str = s;
	while (*str && n-- > 0)
		str++;
	return (str - s);
}
