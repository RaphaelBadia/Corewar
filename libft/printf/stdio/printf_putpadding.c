/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putpadding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 18:11:51 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:24:49 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio_.h"

void	putpadding(t_pf *data, int nb_len_with_padding, int width, char padwith)
{
	while (nb_len_with_padding < width)
	{
		buffwrite_c(data, padwith);
		nb_len_with_padding++;
	}
}
