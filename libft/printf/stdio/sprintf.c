/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:37:10 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/19 16:42:37 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "stdio_.h"

int			ft_sprintf(char *str, const char *format, ...)
{
	va_list	ap;
	int		count;
	t_pf	data;

	prepare_info_data(&data);
	data.fd = 1;
	data.buff_sprintf = 1;
	data.full_buff = str;
	(void)str;
	va_start(ap, format);
	count = ft_vprintf_withinfo(format, ap, &data);
	data.full_buff[data.buff_idx] = '\0';
	if (data.error)
		count = -1;
	va_end(ap);
	return (count);
}
