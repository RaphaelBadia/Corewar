/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_wchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 21:37:23 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 19:12:01 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "stdio_.h"

ssize_t		printf_wchar(va_list ap, void *datavoid)
{
	t_pf	*data;

	data = (t_pf *)datavoid;
	set_bitwise_flag(&(data->length_modifier), 3);
	return (printf_char(ap, data));
}
