/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:37:10 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/17 16:25:44 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "stdio_.h"

int			ft_printf(const char *restrict format, ...)
{
	va_list	ap;
	int		count;
	t_pf	data;

	prepare_info_data(&data);
	data.fd = 1;
	va_start(ap, format);
	count = ft_vprintf_withinfo(format, ap, &data);
	if (-1 == write(data.fd, data.buffer, data.buff_idx) || data.error)
		count = -1;
	va_end(ap);
	return (count);
}
