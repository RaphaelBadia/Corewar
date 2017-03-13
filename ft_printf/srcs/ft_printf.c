/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 00:00:00 by jye               #+#    #+#             */
/*   Updated: 2017/03/12 18:20:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	magic_print(char **format, t_format *c_flag)
{
	char	*f;
	char	*s_modulo;
	int		to_w;

	f = *format;
	s_modulo = ft_strchrnul(f, 0x25);
	to_w = s_modulo - f;
	c_flag->buffer.w(&c_flag->buffer, f, to_w);
	*format += to_w;
	return (to_w);
}

int			ft_printf(const char *format, ...)
{
	va_list		arg;
	t_format	c_da;

	if (format == NULL)
		return (0);
	va_start(arg, format);
	init_t_buffer__(1, &c_da.buffer);
	while (*format)
	{
		if (*format == 0x25)
		{
			format += 1;
			magic(&c_da, (char **)&format, arg);
			magic_conv(&c_da, arg);
		}
		magic_print((char **)&format, &c_da);
	}
	va_end(arg);
	write(1, c_da.buffer.buff, c_da.buffer.i);
	return (c_da.buffer.z);
}

int			ft_dprintf(const int fd, const char *format, ...)
{
	va_list		arg;
	t_format	c_da;

	if (format == NULL)
		return (0);
	va_start(arg, format);
	init_t_buffer__(fd, &c_da.buffer);
	while (*format)
	{
		if (*format == 0x25)
		{
			format += 1;
			magic(&c_da, (char **)&format, arg);
			magic_conv(&c_da, arg);
		}
		magic_print((char **)&format, &c_da);
	}
	va_end(arg);
	write(fd, c_da.buffer.buff, c_da.buffer.i);
	return (c_da.buffer.z);
}
