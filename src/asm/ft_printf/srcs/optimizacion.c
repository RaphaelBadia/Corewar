/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizacion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 20:50:38 by jye               #+#    #+#             */
/*   Updated: 2016/12/30 19:52:21 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void		print_padding(int lpad, char cpad, struct s_buffer *buffer)
{
	if (lpad + buffer->i > IO_STREAM)
	{
		write(1, buffer->buff, buffer->i);
		buffer->i = 0;
	}
	if (lpad > IO_STREAM)
	{
		ft_memset(buffer->buff, cpad, IO_STREAM);
		while (lpad >= IO_STREAM)
		{
			write(1, buffer->buff, IO_STREAM);
			buffer->z += IO_STREAM;
			lpad -= IO_STREAM;
		}
		write(1, buffer->buff, lpad);
		buffer->z += lpad;
	}
	else
	{
		ft_memset(buffer->buff + buffer->i, cpad, lpad);
		buffer->i += lpad;
		buffer->z += lpad;
	}
}

void		print_precision(int lprec, struct s_buffer *buffer)
{
	if (lprec + buffer->i > IO_STREAM)
	{
		write(1, buffer->buff, buffer->i);
		buffer->i = 0;
	}
	if (lprec > IO_STREAM)
	{
		ft_memset(buffer->buff, 0x30, IO_STREAM);
		while (lprec >= IO_STREAM)
		{
			write(1, buffer->buff, IO_STREAM);
			buffer->z += IO_STREAM;
			lprec -= IO_STREAM;
		}
		write(1, buffer->buff, lprec);
		buffer->z += lprec;
	}
	else
	{
		ft_memset(buffer->buff + buffer->i, 0x30, lprec);
		buffer->i += lprec;
		buffer->z += lprec;
	}
}

void		write_t_buffer__(struct s_buffer *buffer, void *s, unsigned long n)
{
	char *buff;

	if (n + buffer->i > IO_STREAM)
	{
		write(1, buffer->buff, buffer->i);
		buffer->i = 0;
	}
	if (n > IO_STREAM)
	{
		if (!(buff = (char *)malloc(sizeof(char) * n)))
			exit(EXIT_FAILURE);
		ft_memcpy(buff, s, n);
		write(1, buff, n);
		buffer->z += n;
		free(buff);
	}
	else
	{
		ft_memcpy(buffer->buff + buffer->i, s, n);
		buffer->i += n;
		buffer->z += n;
	}
}

void		init_t_buffer__(t_buffer *buffer)
{
	buffer->z = 0;
	buffer->i = 0;
	buffer->w = &write_t_buffer__;
}
