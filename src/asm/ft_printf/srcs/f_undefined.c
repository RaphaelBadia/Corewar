/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_undefined.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 20:32:26 by jye               #+#    #+#             */
/*   Updated: 2016/12/13 19:53:03 by jye              ###   ########.fr       */
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

void		f_undefined(t_format *c_flag)
{
	t_conv	tmp;
	char	undef;

	if ((c_flag->flag & 10) == 10)
		c_flag->flag ^= 8;
	tmp.cpad = c_flag->flag & 8 ? 0x30 : 0x20;
	tmp.size = 1;
	undef = c_flag->format;
	tmp.content = &undef;
	if (c_flag->pad != 0)
	{
		pp_handler(c_flag, &tmp);
		return ;
	}
	if (undef)
		c_flag->buffer.w(&c_flag->buffer, &undef, 1);
}
