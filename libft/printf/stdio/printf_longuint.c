/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_longuint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 15:36:33 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 19:11:52 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "math_.h"
#include "string_.h"
#include "stdio_.h"

ssize_t		printf_longuint(va_list ap, void *datavoid)
{
	t_pf	*data;

	data = (t_pf *)datavoid;
	data->length_modifier = 0;
	set_bitwise_flag(&(data->length_modifier), 3);
	return (printf_uint(ap, data));
}
