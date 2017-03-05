/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_printable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:06:39 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/05 10:54:38 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "string_.h"
#include "math_.h"
#include "stdio_.h"

ssize_t		put_printable(va_list ap, t_pf *data)
{
	unsigned char	*str;
	size_t			len;

	str = va_arg(ap, unsigned char *);
	if (str == NULL)
		str = (unsigned char *)"(null)";
	if (data->precision == -1)
		len = 0;
	else if (data->precision > 0)
		len = strnlen_((char *)str, data->precision);
	else
		len = strlen_((char *)str);
	if (data->min_width > 0 && data->flag_padleft == 0)
		putpadding(data, len, data->min_width, data->flag_pad0 ? '0' : ' ');
	len = putsprintable_n_buf(data, str, len);
	if (data->min_width > 0 && data->flag_padleft != 0)
		putpadding(data, len, data->min_width, ' ');
	return (data->min_width ? max_(len, data->min_width) : len);
}

ssize_t		printf_printable(va_list ap, void *datavoid)
{
	t_pf	*data;

	data = (t_pf *)datavoid;
	return (put_printable(ap, data) - 1);
}
