/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_longint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:43:50 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 19:11:43 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "stdio_.h"

ssize_t		printf_longint(va_list ap, void *datavoid)
{
	t_pf	*data;

	data = (t_pf *)datavoid;
	data->length_modifier = 0;
	set_bitwise_flag(&(data->length_modifier), 3);
	return (printf_int(ap, data));
}
