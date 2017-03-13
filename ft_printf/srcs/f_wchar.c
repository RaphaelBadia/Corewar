/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_wchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 18:45:59 by jye               #+#    #+#             */
/*   Updated: 2016/12/13 19:54:06 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

static void	pp_handler__(t_format *c_flag, t_conv *tmp)
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

void		f_wchar(t_format *c_flag, va_list arg)
{
	int		wchar;
	char	a[5];
	t_conv	tmp;

	if ((c_flag->flag & 10) == 10)
		c_flag->flag ^= 8;
	tmp.cpad = c_flag->flag & 8 ? 0x30 : 0x20;
	wchar = va_arg(arg, int);
	tmp.size = w_char(wchar, a);
	tmp.content = a;
	if (c_flag->pad != 0)
		pp_handler__(c_flag, &tmp);
	else
		c_flag->buffer.w(&c_flag->buffer, a, tmp.size);
}
