/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_set_width.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:59:42 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 18:01:17 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctype_.h"
#include "stdio_.h"

const char		*set_min_width(const char *format, t_pf *data)
{
	int		result;

	result = 0;
	while (isdigit_(*format))
		result = result * 10 + (*format++ - '0');
	data->min_width = result;
	return (format);
}
