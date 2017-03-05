/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flag_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:54:22 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 17:57:46 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_.h"
#include "stdio_.h"

int				set_bitwise_flag(char *flag, int index)
{
	return (*flag |= (1 << 7 >> index));
}

int				set_bitwise_flag_zero(char *flag, int index)
{
	return (*flag &= (0 << 7 >> index));
}

int				get_bitwise_flag(char flag, int index)
{
	return (((flag << index) >> 7) & 1);
}

void			clear_flags(t_pf *data)
{
	if (data->flag_addplus && data->flag_addspace)
		data->flag_addspace = 0;
	if (data->flag_padleft && data->flag_pad0)
		data->flag_pad0 = 0;
}

const char		*set_flags(const char *format, t_pf *data)
{
	const char	*flag_ptr;
	int			index;

	flag_ptr = strchr_i(PRINTF_FLAGS, *format, &index);
	if (flag_ptr != NULL)
	{
		if (*flag_ptr == '-')
			data->flag_padleft = 1;
		else if (*flag_ptr == '+')
			data->flag_addplus = 1;
		else if (*flag_ptr == '#')
			data->flag_sharp = 1;
		else if (*flag_ptr == '0')
			data->flag_pad0 = 1;
		else if (*flag_ptr == ' ')
			data->flag_addspace = 1;
		return (set_flags(format + 1, data));
	}
	return (format);
}
