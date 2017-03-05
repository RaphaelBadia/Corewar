/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putwc_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 17:42:36 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 21:54:31 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include "stdio_.h"

void	putwc_fd(const int fd, wchar_t chr)
{
	if (chr <= 0x7F)
		putc_fd(fd, chr);
	else if (chr <= 0x7FF)
	{
		putc_fd(fd, (chr >> 6) + 0xC0);
		putc_fd(fd, (chr & 0x3F) + 0x80);
	}
	else if (chr <= 0xFFFF)
	{
		putc_fd(fd, (chr >> 12) + 0xE0);
		putc_fd(fd, ((chr >> 6) & 0x3F) + 0x80);
		putc_fd(fd, (chr & 0x3F) + 0x80);
	}
	else if (chr <= 0x10FFFF)
	{
		putc_fd(fd, (chr >> 18) + 0xF0);
		putc_fd(fd, ((chr >> 12) & 0x3F) + 0x80);
		putc_fd(fd, ((chr >> 6) & 0x3F) + 0x80);
		putc_fd(fd, (chr & 0x3F) + 0x80);
	}
}
