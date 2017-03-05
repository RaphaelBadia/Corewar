/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_set_size_modifier.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 18:03:16 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 20:59:52 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_.h"
#include "stdio_.h"

const char		*set_size(const char *format, t_pf *data)
{
	int			i;
	int			modifier_len;

	i = 0;
	while (i < MODIFIERS_LEN)
	{
		modifier_len = strlen_(data->modifiers[i]);
		if (strncmp_(format, data->modifiers[i], modifier_len) == 0)
		{
			set_bitwise_flag(&data->length_modifier, i);
			format += modifier_len;
			break ;
		}
		i++;
	}
	return (format);
}
