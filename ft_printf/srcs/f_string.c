/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_string.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:41:05 by jye               #+#    #+#             */
/*   Updated: 2016/12/13 17:48:19 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pp_handler(t_format *c_flag, t_conv *tmp)
{
	int		pad;

	pad = c_flag->pad - tmp->size;
	if (c_flag->flag & 2)
	{
		c_flag->buffer.w(&c_flag->buffer, tmp->content, tmp->size);
		if (pad > 0)
			print_padding(pad, tmp->cpad, &c_flag->buffer);
	}
	else
	{
		if (pad > 0)
			print_padding(pad, tmp->cpad, &c_flag->buffer);
		c_flag->buffer.w(&c_flag->buffer, tmp->content, tmp->size);
	}
}

void		f_string(t_format *c_flag, va_list arg)
{
	char		*s;
	t_conv		tmp;

	if (c_flag->length == 4)
		return (f_wstring(c_flag, arg));
	else
	{
		s = va_arg(arg, char *);
		if (!s)
			s = SNULL;
		if ((c_flag->flag & 10) == 10)
			c_flag->flag ^= 8;
		tmp.cpad = c_flag->flag & 8 ? 0x30 : 0x20;
		tmp.size = ft_strlen(s);
		tmp.content = s;
		if (c_flag->flag & 32)
			if (c_flag->precision >= 0 &&
				(unsigned int)c_flag->precision < tmp.size)
				tmp.size = c_flag->precision;
		if (c_flag->pad != 0)
			pp_handler(c_flag, &tmp);
		else
			c_flag->buffer.w(&c_flag->buffer, s, tmp.size);
	}
}
