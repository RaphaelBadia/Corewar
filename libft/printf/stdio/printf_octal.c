/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 22:14:38 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:56:49 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "math_.h"
#include "string_.h"
#include "stdio_.h"

static uintmax_t	cast_uint(uintmax_t to_cast, t_pf *data)
{
	uintmax_t		cast;

	if (IS_HH_MODIFIER)
		cast = (unsigned char)to_cast;
	else if (IS_H_MODIFIER)
		cast = (unsigned short)to_cast;
	else if (IS_L_MODIFIER)
		cast = (unsigned long)to_cast;
	else if (IS_LL_MODIFIER)
		cast = (unsigned long long)to_cast;
	else if (IS_J_MODIFIER)
		cast = (uintmax_t)to_cast;
	else if (IS_T_MODIFIER)
		cast = (ptrdiff_t)to_cast;
	else if (IS_Z_MODIFIER)
		cast = (size_t)to_cast;
	else
		cast = (unsigned int)to_cast;
	return (cast);
}

ssize_t				printf_octal(va_list ap, void *datavoid)
{
	t_pf			*data;
	uintmax_t		nb;

	data = (t_pf *)datavoid;
	nb = cast_uint(va_arg(ap, uintmax_t), data);
	if (data->flag_addplus)
		data->flag_addplus = 0;
	if ((data->flag_sharp || data->flag_addplus) && nb == 0
	&& data->precision == -1)
	{
		if (data->min_width > 0 && data->flag_padleft == 0)
			putpadding(data, 1, data->min_width, data->flag_pad0 ? '0' : ' ');
		if (data->flag_sharp)
			puts_buf(data, "0");
		if (data->min_width && data->flag_pad0)
			putpadding(data, 1, data->min_width, ' ');
		return (data->min_width ? max_(data->min_width, 1) : 1);
	}
	else if ((data->flag_sharp || data->flag_addplus) && nb != 0)
		data->precision = max_((data->precision == -1 ? 0 : data->precision),
			nbrbase_len(nb, "01234567") + 1);
	return (put_uint(nb, data, "01234567", NULL));
}

ssize_t				printf_long_octal(va_list ap, void *datavoid)
{
	t_pf			*data;

	data = (t_pf *)datavoid;
	data->length_modifier = 0;
	set_bitwise_flag(&(data->length_modifier), 3);
	return (printf_octal(ap, data));
}
