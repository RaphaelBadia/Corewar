/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_wstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:10:29 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:36:43 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "math_.h"
#include "stdio_.h"

size_t	calc_wstrlen(wchar_t *str, int precision, size_t i)
{
	if (*str == '\0' || precision == 0)
		return (i);
	else if (*str <= 0x7F)
		return (calc_wstrlen(str + 1, precision - 1, i + 1));
	else if (*str <= 0x7FF && precision >= 2)
		return (calc_wstrlen(str + 1, precision - 2, i + 2));
	else if (*str <= 0xFFFF && precision >= 3)
		return (calc_wstrlen(str + 1, precision - 3, i + 3));
	else if (*str <= 0x10FFFF && precision >= 4)
		return (calc_wstrlen(str + 1, precision - 4, i + 4));
	else
		return (i);
}

size_t	ft_wstrlen(wchar_t *str)
{
	size_t i;

	i = 0;
	while (*str)
	{
		if (*str <= 0x7F)
			i++;
		else if (*str <= 0x7FF)
			i += 2;
		else if (*str <= 0xFFFF)
			i += 3;
		else if (*str <= 0x10FFFF)
			i += 4;
		str++;
	}
	return (i);
}

ssize_t	printf_wstr(va_list ap, void *datavoid)
{
	wchar_t	*str;
	size_t	len;
	t_pf	*data;

	data = (t_pf *)datavoid;
	str = va_arg(ap, wchar_t*);
	if (str == NULL)
		str = L"(null)";
	if (data->precision == -1)
		len = 0;
	else if (data->precision > 0)
		len = calc_wstrlen(str, data->precision, 0);
	else
		len = ft_wstrlen(str);
	if (data->min_width > 0 && data->flag_padleft == 0)
		putpadding(data, len, data->min_width, data->flag_pad0 ? '0' : ' ');
	putwsn_buf(data, str, len);
	if (data->min_width && data->flag_padleft)
		putpadding(data, len, data->min_width, ' ');
	return (data->min_width ? max_(len, data->min_width) : len);
}
