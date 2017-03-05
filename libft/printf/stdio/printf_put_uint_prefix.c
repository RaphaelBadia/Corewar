/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_put_uint_prefix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 20:50:06 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:56:30 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_.h"
#include "string_.h"
#include "stdio_.h"

int		put_uint_prefix(uintmax_t nb, char *b, t_pf *data, char *p)
{
	uintmax_t	nb_len;
	size_t		nb_cut;

	nb_len = calculate_strlen_from_nbr(nb, b, NULL, data) + strlen_(p);
	nb_cut = strlen_(p);
	if (data->min_width > 0 && data->flag_padleft == 0 && data->flag_pad0 == 0)
	{
		putpadding(data, nb_len, data->min_width, ' ');
		nb_cut += max_(data->min_width - nb_len, 0);
		data->min_width = 0;
	}
	else if (data->min_width > 0)
		data->min_width -= strlen_(p);
	puts_buf(data, p);
	return (put_uint(nb, data, b, NULL) + nb_cut);
}
