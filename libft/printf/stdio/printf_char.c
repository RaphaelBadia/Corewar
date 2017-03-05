/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 21:37:23 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/03 00:36:07 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include <stdarg.h>
#include "math_.h"
#include "stdio_.h"

ssize_t			put_wchar(va_list ap, t_pf *data)
{
	wchar_t		chr;
	unsigned	chr_len;

	chr = (wchar_t)va_arg(ap, wchar_t);
	if (chr <= 0x7F)
		chr_len = 1;
	else if (chr <= 0x7FF)
		chr_len = 2;
	else if (chr <= 0xFFFF)
		chr_len = 3;
	else if (chr <= 0x10FFFF)
		chr_len = 4;
	else
		chr_len = 0;
	if (data->min_width > 0 && data->flag_padleft == 0)
		putpadding(data, chr_len, data->min_width, data->flag_pad0 ? '0' : ' ');
	putwc_buf(data, chr);
	if (data->min_width > 0 && data->flag_padleft)
		putpadding(data, chr_len, data->min_width, data->flag_pad0 ? '0' : ' ');
	return (data->min_width > 0 ? max_(chr_len, data->min_width) : chr_len);
}

ssize_t			printf_char(va_list ap, void *datavoid)
{
	t_pf		*data;

	data = (t_pf *)datavoid;
	if (IS_L_MODIFIER)
		return (put_wchar(ap, data));
	else
	{
		if (data->min_width > 0 && data->flag_padleft == 0)
		{
			if (data->flag_pad0)
				putpadding(data, 1, data->min_width, '0');
			else
				putpadding(data, 1, data->min_width, ' ');
		}
		buffwrite_c(data, va_arg(ap, int));
		if (data->min_width && data->flag_padleft)
			putpadding(data, 1, data->min_width, ' ');
		if (data->min_width > 0)
			return (max_(data->min_width, 1));
		else
			return (1);
	}
}
