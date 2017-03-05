/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_big_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:36:33 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 20:45:06 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "math_.h"
#include "string_.h"
#include "stdio_.h"

static uintmax_t	cast_hex(uintmax_t to_cast, t_pf *data)
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

ssize_t				printf_big_hex(va_list ap, void *datavoid)
{
	t_pf			*data;
	uintmax_t		nbr;

	data = (t_pf *)datavoid;
	nbr = cast_hex(va_arg(ap, uintmax_t), data);
	if (data->flag_addplus)
		return (put_uint(nbr, data, "0123456789ABCDEF", NULL));
	return (put_uint(nbr, data, "0123456789ABCDEF", "0X"));
}
