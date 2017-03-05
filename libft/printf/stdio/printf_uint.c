/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 11:02:32 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:57:07 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "math_.h"
#include "string_.h"
#include "stdio_.h"

static void			transform_width_to_precision(t_pf *data, int nb_len)
{
	if (data->precision)
		data->precision = max_(data->min_width, data->precision);
	else
		data->precision = max_(data->min_width, nb_len);
	data->min_width = 0;
}

/*
** Affiche un unsigned int
**
** 1.calcule la taille du nombre en ajoutant les 0
** 2.ajoute des espaces devant si il n'y a pas le flag -
** 3.affiche le -, + ou l'espace avant le nombre
** 4.affiche les espaces avant le nombre
** 4.affiche le nombre (avec les 0 devant)
** 5.affiche les espaces après le nombre
*/

ssize_t				put_uint(uintmax_t nb, t_pf *data, char *b, char *prefix)
{
	size_t			nb_len_withpadding;
	int				written_count;

	written_count = 0;
	if (data->min_width > 0 && data->flag_pad0)
		transform_width_to_precision(data, nbrbase_len(nb, b));
	nb_len_withpadding = nbrlen_withpadding(nb, b, prefix, data);
	if (data->min_width && !data->flag_padleft)
		putpadding(data, nb_len_withpadding, data->min_width, ' ');
	if ((data->flag_addplus || data->flag_sharp) && prefix != NULL && nb != 0)
		written_count += puts_buf(data, prefix);
	putnbr_base_with_precision(nb, b, data);
	if (data->min_width && data->flag_padleft)
		putpadding(data, nb_len_withpadding, data->min_width, ' ');
	if (data->min_width > 0)
		written_count += max_(nb_len_withpadding, data->min_width);
	else
		written_count += nb_len_withpadding;
	return (written_count);
}

static uintmax_t	cast_uint(uintmax_t to_cast, t_pf *data)
{
	uintmax_t		cast;

	if (IS_HH_MODIFIER)
		cast = (unsigned char)to_cast;
	else if (IS_H_MODIFIER)
		cast = (unsigned short)to_cast;
	else if (IS_L_MODIFIER)
		cast = (unsigned long)to_cast;
	else if (IS_LL_MODIFIER)
		cast = (unsigned long long)to_cast;
	else if (IS_J_MODIFIER)
		cast = (uintmax_t)to_cast;
	else if (IS_T_MODIFIER)
		cast = (ptrdiff_t)to_cast;
	else if (IS_Z_MODIFIER)
		cast = (size_t)to_cast;
	else
		cast = (unsigned int)to_cast;
	return (cast);
}

ssize_t				printf_uint(va_list ap, void *datavoid)
{
	uintmax_t		nb;

	nb = va_arg(ap, uintmax_t);
	nb = cast_uint(nb, (t_pf *)datavoid);
	return (put_uint(nb, (t_pf *)datavoid, "0123456789", NULL));
}
