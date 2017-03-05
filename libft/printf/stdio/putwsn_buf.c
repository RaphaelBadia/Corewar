/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putwsn_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:04:55 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:59:55 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "stdio_.h"

void	putwsn_buf(t_pf *data, wchar_t const *str, size_t size)
{
	size_t i;

	i = 0;
	while (*str)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		if (i <= size)
			putwc_buf(data, *str);
		str++;
	}
}
