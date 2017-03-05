/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_set_precision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 18:01:46 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 18:01:52 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype_.h"
#include "stdio_.h"

const char		*set_precision(const char *format, t_pf *data)
{
	int		result;

	result = 0;
	if (*format == '.')
	{
		format++;
		while (isdigit_(*format))
			result = result * 10 + (*format++ - '0');
		if (result == 0)
			data->precision = -1;
		else
			data->precision = result;
	}
	return (format);
}
