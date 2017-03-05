/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:06:39 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:41:33 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "string_.h"
#include "math_.h"
#include "stdio_.h"

ssize_t		put_str(va_list ap, t_pf *data)
{
	char	*str;
	size_t	len;

	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	if (data->precision == -1)
		len = 0;
	else if (data->precision > 0)
		len = strnlen_(str, data->precision);
	else
		len = strlen_(str);
	if (data->min_width > 0 && data->flag_padleft == 0)
		putpadding(data, len, data->min_width, data->flag_pad0 ? '0' : ' ');
	puts_n_buf(data, str, len);
	if (data->min_width > 0 && data->flag_padleft != 0)
		putpadding(data, len, data->min_width, ' ');
	return (data->min_width ? max_(len, data->min_width) : len);
}

ssize_t		printf_str(va_list ap, void *datavoid)
{
	t_pf	*data;

	data = (t_pf *)datavoid;
	if (IS_L_MODIFIER)
		return (printf_wstr(ap, data));
	else
		return (put_str(ap, data));
}
