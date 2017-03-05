/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:07:57 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:34:04 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "string_.h"
#include "math_.h"
#include "stdio_.h"

ssize_t			printf_ptr(va_list ap, void *datavoid)
{
	t_pf		*data;
	uintmax_t	nbr;

	data = (t_pf *)datavoid;
	if (data->precision > 0)
		data->flag_pad0 = 0;
	nbr = va_arg(ap, uintmax_t);
	return (put_uint_prefix(nbr, "0123456789abcdef", data, "0x"));
}
