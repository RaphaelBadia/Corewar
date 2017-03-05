/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putwc_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:42:36 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:52:35 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "stdio_.h"

void	putwc_buf(t_pf *data, wchar_t chr)
{
	if (chr <= 0x7F)
		buffwrite_c(data, chr);
	else if (chr <= 0x7FF)
	{
		buffwrite_c(data, (chr >> 6) + 0xC0);
		buffwrite_c(data, (chr & 0x3F) + 0x80);
	}
	else if (chr <= 0xFFFF)
	{
		buffwrite_c(data, (chr >> 12) + 0xE0);
		buffwrite_c(data, ((chr >> 6) & 0x3F) + 0x80);
		buffwrite_c(data, (chr & 0x3F) + 0x80);
	}
	else if (chr <= 0x10FFFF)
	{
		buffwrite_c(data, (chr >> 18) + 0xF0);
		buffwrite_c(data, ((chr >> 12) & 0x3F) + 0x80);
		buffwrite_c(data, ((chr >> 6) & 0x3F) + 0x80);
		buffwrite_c(data, (chr & 0x3F) + 0x80);
	}
}
