/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smprintf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:37:10 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/06 18:57:56 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "string_.h"
#include "stdio_.h"

int			ft_smprintf(char **str, const char *format, ...)
{
	va_list	ap;
	int		count;
	t_pf	data;
	char	*buffer_tmp;

	prepare_info_data(&data);
	data.fd = 1;
	data.bufferise_whole_printf = 1;
	data.full_buff = strdup_("");
	if (data.full_buff == NULL)
		return (-1);
	va_start(ap, format);
	count = ft_vprintf_withinfo(format, ap, &data);
	data.buffer[data.buff_idx] = '\0';
	buffer_tmp = strjoin_(data.full_buff, data.buffer);
	free(data.full_buff);
	*str = buffer_tmp;
	if (buffer_tmp == NULL)
		return (-1);
	if (data.error)
		count = -1;
	va_end(ap);
	return (count);
}
