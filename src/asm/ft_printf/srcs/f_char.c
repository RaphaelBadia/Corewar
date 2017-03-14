/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_char.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:49:17 by jye               #+#    #+#             */
/*   Updated: 2016/12/13 19:52:01 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	pp_handler(t_format *c_flag, t_conv *tmp)
{
	int		pad;

	pad = c_flag->pad - tmp->size;
	if (c_flag->flag & 2)
	{
		c_flag->buffer.w(&c_flag->buffer, tmp->content, 1);
		if (pad > 0)
			print_padding(pad, tmp->cpad, &c_flag->buffer);
	}
	else
	{
		if (pad > 0)
			print_padding(pad, tmp->cpad, &c_flag->buffer);
		c_flag->buffer.w(&c_flag->buffer, tmp->content, 1);
	}
}

void		f_char(t_format *c_flag, va_list arg)
{
	int		op;
	t_conv	tmp;

	if (c_flag->length == 4)
		return (f_wchar(c_flag, arg));
	else
	{
		if ((c_flag->flag & 10) == 10)
			c_flag->flag ^= 8;
		tmp.cpad = c_flag->flag & 8 ? 0x30 : 0x20;
		tmp.size = 1;
		op = 0xff & va_arg(arg, int);
		tmp.content = &op;
		if (c_flag->pad != 0)
			pp_handler(c_flag, &tmp);
		else
			c_flag->buffer.w(&c_flag->buffer, &op, 1);
	}
}
