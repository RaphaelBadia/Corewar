/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_strlen_from_nbr.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 10:39:23 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 20:44:29 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_.h"
#include "math_.h"
#include "stdio_.h"

unsigned int	calculate_strlen_from_nbr(uintmax_t nb, char *b, char *p,
	t_pf *data)
{
	size_t		nb_len;

	if (nb == 0 && data->precision == -1)
		nb_len = 0;
	else if (data->precision > 0)
		nb_len = max_(nbrbase_len(nb, b), data->precision);
	else
		nb_len = nbrbase_len(nb, b);
	if (data->flag_addplus && p != NULL && nb != 0)
		nb_len += strlen_(p);
	return (nb_len);
}
