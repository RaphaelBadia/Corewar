/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbrbase_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 10:44:32 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 19:15:24 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "string_.h"

unsigned int	nbrbase_len(uintmax_t nb, char *b)
{
	size_t			base_nbr;
	unsigned int	i;

	base_nbr = strlen_(b);
	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb /= base_nbr;
		i++;
	}
	return (i);
}
