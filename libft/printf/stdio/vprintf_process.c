/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vprintf_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:37:10 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:56:09 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ctype_.h"
#include "string_.h"
#include "stdio_.h"

const char		*print_arg(const char *format, va_list ap, t_pf *data)
{
	const char	*save;

	save = format;
	format = set_flags(format, data);
	format = set_min_width(format, data);
	format = set_precision(format, data);
	format = set_size(format, data);
	clear_flags(data);
	if ((format = set_conv_type(format, ap, data)) == NULL)
		return (save);
	return (format);
}

static void		reset_printf_data(t_pf *data)
{
	data->flag_padleft = 0;
	data->flag_addplus = 0;
	data->flag_sharp = 0;
	data->flag_pad0 = 0;
	data->flag_addspace = 0;
	data->length_modifier = 0;
	data->precision = 0;
	data->min_width = 0;
}

int				ft_vprintf_withinfo(const char *format, va_list ap, t_pf *data)
{
	const char	*next_arg;
	int			count;

	count = 0;
	if (*format == '\0' || (next_arg = strchr_(format, '%')) == NULL)
		return (count + puts_buf(data, format));
	if (*format == '%')
	{
		data->printed_char = 0;
		if ((next_arg = print_arg(format + 1, ap, data)) == format)
			return (count + ft_vprintf_withinfo(format + 1, ap, data));
		count += data->printed_char;
		reset_printf_data(data);
	}
	else
		count += puts_n_buf(data, format, next_arg - format);
	return (count + ft_vprintf_withinfo(next_arg, ap, data));
}
