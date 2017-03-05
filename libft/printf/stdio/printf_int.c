/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:02:11 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 21:28:35 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <stdarg.h>
#include "stdio_.h"
#include "stdlib_.h"
#include "string_.h"
#include "math_.h"

static intmax_t	cast_int(intmax_t to_cast, t_pf *data)
{
	intmax_t	cast;

	if (IS_HH_MODIFIER)
		cast = (signed char)to_cast;
	else if (IS_H_MODIFIER)
		cast = (short)to_cast;
	else if (IS_L_MODIFIER)
		cast = (long)to_cast;
	else if (IS_LL_MODIFIER)
		cast = (long long)to_cast;
	else if (IS_J_MODIFIER)
		cast = to_cast;
	else if (IS_T_MODIFIER)
		cast = (ptrdiff_t)to_cast;
	else if (IS_Z_MODIFIER)
		cast = (size_t)to_cast;
	else if (IS_BIG_L_MODIFIER)
		cast = (size_t)to_cast;
	else
		cast = (int)to_cast;
	return (cast);
}

ssize_t			printf_int(va_list ap, void *datavoid)
{
	intmax_t	nb;
	char		*prefix;
	t_pf		*data;

	data = (t_pf *)datavoid;
	nb = cast_int(va_arg(ap, intmax_t), data);
	if (data->precision > 0)
		data->flag_pad0 = 0;
	if (nb < 0 || data->flag_addplus || data->flag_addspace)
	{
		if (nb < 0)
		{
			nb = -nb;
			prefix = "-";
		}
		else if (data->flag_addplus)
			prefix = "+";
		else
			prefix = " ";
		return (put_uint_prefix(nb, "0123456789", data, prefix));
	}
	else
		return (put_uint(nb, datavoid, "0123456789", NULL));
}
