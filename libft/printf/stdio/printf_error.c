/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:08:39 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 21:51:45 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "math_.h"
#include "stdio_.h"

ssize_t	printf_error(va_list ap, void *datavoid)
{
	t_pf	*data;

	data = (t_pf *)datavoid;
	(void)ap;
	if (data->precision == -1)
		data->precision++;
	if (data->flag_padleft)
		buffwrite_c(data, data->char_to_print);
	if (data->min_width > 0 && data->flag_padleft == 0)
		putpadding(data, data->precision, data->min_width - 1,
			data->flag_pad0 ? '0' : ' ');
	if (data->min_width > 0 && data->flag_padleft != 0)
		putpadding(data, data->precision, data->min_width - 1, ' ');
	if (!data->flag_padleft)
		buffwrite_c(data, data->char_to_print);
	return ((data->min_width ? max_(data->precision,
		data->min_width - 1) : data->precision) + 1);
}
