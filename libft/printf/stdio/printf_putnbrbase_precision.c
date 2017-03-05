/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putnbrbase_precision.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 18:37:18 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:28:23 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_.h"
#include "stdio_.h"

static void		putnbrbase_fd_inner(uintmax_t nb, char *b, t_pf *data)
{
	uintmax_t	blen;

	blen = strlen_(b);
	if (nb >= blen)
	{
		putnbrbase_fd_inner(nb / blen, b, data);
		putnbrbase_fd_inner(nb % blen, b, data);
	}
	else
		buffwrite_c(data, b[nb]);
}

/*
** affiche un nombre avec des 0 devant si une precision / min_width est demandée
*/

void			putnbr_base_with_precision(uintmax_t nb, char *b, t_pf *data)
{
	if (data->precision > 0)
		putpadding(data, nbrbase_len(nb, b), data->precision, b[0]);
	if (nb == 0 && data->precision == -1)
		return ;
	else
		putnbrbase_fd_inner(nb, b, data);
}
