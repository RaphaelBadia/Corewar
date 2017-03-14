/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 00:00:00 by jye               #+#    #+#             */
/*   Updated: 2016/12/27 15:08:48 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static int	magic_print(char **format, t_format *c_flag)
{
	char	*f;
	char	*s_modulo;
	char	*s_bracket;
	char	*actual;
	int		to_w;

	f = *format;
	s_modulo = ft_strchrnul(f, 0x25);
	s_bracket = ft_memchr(f, 0x7b, s_modulo - f);
	actual = s_bracket ? s_bracket : s_modulo;
	to_w = actual - f;
	c_flag->buffer.w(&c_flag->buffer, f, to_w);
	*format += to_w;
	return (to_w);
}

static int	is_color(char *buff, t_format *c_flag)
{
	char	bool__;

	bool__ = 0;
	if (!ft_strcmp(buff, "{black}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, BLACK, 5);
	else if (!ft_strcmp(buff, "{red}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, RED, 5);
	else if (!ft_strcmp(buff, "{green}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, GREEN, 5);
	else if (!ft_strcmp(buff, "{yellow}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, YELLOW, 5);
	else if (!ft_strcmp(buff, "{blue}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, BLUE, 5);
	else if (!ft_strcmp(buff, "{magenta}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, MAGENTA, 5);
	else if (!ft_strcmp(buff, "{cyan}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, CYAN, 5);
	else if (!ft_strcmp(buff, "{white}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, WHITE, 5);
	else if (!ft_strcmp(buff, "{eos}") && (bool__ = 1))
		c_flag->buffer.w(&c_flag->buffer, CRESET, 4);
	return (bool__);
}

static int	is_modulo(char *buff)
{
	char *a;

	a = buff;
	while (*a != 0x25 && *a)
		++a;
	return (a - buff);
}

static void	magic_color(char **color, t_format *c_flag)
{
	char	*f;
	char	buff[11];
	int		i;

	f = *color;
	i = -1;
	while (++i < 10 && f[i] && f[i] != 0x7d)
		buff[i] = f[i];
	if (f[i] == 0x7d)
		buff[i++] = 0x7d;
	buff[i] = 0;
	if (is_color(buff, c_flag))
	{
		*color += i;
		return ;
	}
	else
	{
		i = is_modulo(buff);
		c_flag->buffer.w(&c_flag->buffer, buff, i);
		*color += i;
		return ;
	}
}

int			ft_printf(const char *format, ...)
{
	va_list		arg;
	t_format	c_da;

	if (format == NULL)
		return (0);
	va_start(arg, format);
	init_t_buffer__(&c_da.buffer);
	while (*format)
	{
		if (*format == 0x25)
		{
			format += 1;
			magic(&c_da, (char **)&format, arg);
			magic_conv(&c_da, arg);
		}
		else if (*format == 0x7b)
			magic_color((char **)&format, &c_da);
		magic_print((char **)&format, &c_da);
	}
	va_end(arg);
	write(1, c_da.buffer.buff, c_da.buffer.i);
	return (c_da.buffer.z);
}
