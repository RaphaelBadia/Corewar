/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffwrite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:03:19 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/19 16:43:01 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "string_.h"
#include "stdio_.h"

void			buffwrite_fullbuffered(t_pf *data, char c)
{
	char		*buffer_tmp;

	data->buffer[data->buff_idx] = c;
	if (data->bufferise_whole_printf)
	{
		data->buffer[data->buff_idx + 1] = '\0';
		buffer_tmp = strjoin_(data->full_buff, data->buffer);
		if (buffer_tmp == NULL)
		{
			data->error = 1;
			return ;
		}
		free(data->full_buff);
		data->full_buff = buffer_tmp;
	}
	else
	{
		if (-1 == write(data->fd, data->buffer, data->buff_idx + 1))
			data->error = 1;
	}
	data->buff_idx = 0;
}

void			buffwrite_c(t_pf *data, char c)
{
	if (data->buff_sprintf)
	{
		if (data->buff_idx < data->buff_limit - 1)
			data->full_buff[data->buff_idx++] = c;
		else if (data->buff_idx == data->buff_limit - 1 || !data->buff_limit)
			data->full_buff[data->buff_idx] = '\0';
	}
	else if (data->buff_idx + 1 < PF_BUFF_SIZE)
		data->buffer[data->buff_idx++] = c;
	else
	{
		buffwrite_fullbuffered(data, c);
	}
}
