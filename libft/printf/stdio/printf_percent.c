/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_percent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 12:07:15 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 21:52:13 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "string_.h"
#include "math_.h"
#include "stdio_.h"

ssize_t	printf_percent(va_list ap, void *datavoid)
{
	t_pf	*data;

	(void)ap;
	data = (t_pf *)datavoid;
	if (data->min_width > 0 && data->flag_padleft == 0)
		putpadding(data, 1, data->min_width, data->flag_pad0 ? '0' : ' ');
	buffwrite_c(data, '%');
	if (data->min_width > 0 && data->flag_padleft != 0)
		putpadding(data, 1, data->min_width, ' ');
	return (data->min_width ? max_(1, data->min_width) : 1);
}
