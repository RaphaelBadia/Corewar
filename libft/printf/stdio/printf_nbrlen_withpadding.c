/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_nbrlen_withpadding.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 18:18:57 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 18:22:44 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_.h"
#include "math_.h"
#include "stdio_.h"

/*
** Calcule la taille de la chaine du nombre, en comptant les 0
**
** dans le premier cas, il n'y a rien a rajouter.
** dans le 2eme, si c'est une precision ça veut dire qu'il faut rajouter des 0
** (et donc qu'ils comptent dans la taille du nombre, au contraire des espaces)
*/

unsigned int	nbrlen_withpadding(uintmax_t nb, char *b, char *p, t_pf *data)
{
	unsigned int	nbr_len;
	unsigned int	nbrstrlen;

	nbr_len = nbrbase_len(nb, b);
	if (nb == 0 && data->precision == -1)
		nbrstrlen = 0;
	else if (data->precision)
		nbrstrlen = max_(nbr_len, data->precision);
	else
		nbrstrlen = nbr_len;
	if (data->flag_addplus && p != NULL && nb != 0)
		nbrstrlen += strlen_(p);
	return (nbrstrlen);
}
