/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_set_conv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 18:04:50 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 18:05:01 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_.h"

const char		*set_conv_type(const char *format, va_list ap, t_pf *data)
{
	int			i;

	i = 0;
	while (i < TOTAL_CONV_FUNCTIONS)
	{
		if (*format == data->conv_fts[i].specifier)
		{
			data->printed_char = data->conv_fts[i].ft(ap, data);
			return (format + 1);
		}
		i++;
	}
	if (*format == 0)
		return (format);
	data->char_to_print = *format;
	data->printed_char = printf_error(ap, data);
	return (format + 1);
}
