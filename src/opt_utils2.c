/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_opt2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 17:18:26 by jye               #+#    #+#             */
/*   Updated: 2017/03/10 21:18:14 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "vm.h"

/*
** data[0] = to_get index, data[1] = octal, data[2] = label
*/
unsigned int	nskip(unsigned char byte_code, unsigned char octal_code)
{
	int				i;
	unsigned int	skip;
	unsigned char	octal[3];

	i = 0;
	skip = 2;
	octal[0] = octal_code >> 6;
	octal[1] = (octal_code >> 4) & 3;
	octal[2] = (octal_code >> 2) & 3;
	while (i < g_op_tab[byte_code].argc)
	{
		if (octal[i] == DIR_CODE)
		{
			if (g_op_tab[byte_code].label_size)
				skip += 2;
			else
				skip += 4;
		}
		else if (octal[i] == REG_CODE)
			skip += 1;
		else if (octal[i] == IND_CODE)
			skip += 2;
		++i;
	}
	return (skip);
}
