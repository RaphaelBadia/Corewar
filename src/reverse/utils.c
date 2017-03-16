/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:12:20 by jye               #+#    #+#             */
/*   Updated: 2017/03/16 17:44:02 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_printf.h>
#include <mighty.h>

int					get_uint32(unsigned char *buff, int i)
{
	return ((*(buff + i) << 24) | (*(buff + i + 1) << 16) |
	(*(buff + i + 2) << 8) | (*(buff + i + 3)));
}

short				get_uint16(unsigned char *buff, int i)
{
	return ((*(buff + i) << 8) | (*(buff + i + 1)));
}

int					get_code_value(int code, int is_32_bits_)
{
	if (code == REG_CODE)
		return (1);
	if (code == IND_CODE)
		return (2);
	if (is_32_bits_)
		return (4);
	return (2);
}

void				ft_exit(char *msg)
{
	ft_dprintf(2, "Error: %s\n", msg);
	exit(1);
}

void				aff(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	ft_dprintf(df, "\taff ");
	if (f[0] == REG_CODE)
	{
		ft_dprintf(df, "r%hhd", *(buff + *i));
		*i += 1;
	}
	else if (f[0] == IND_CODE)
	{
		ft_dprintf(df, "%hd", (short)get_uint16(buff, *i));
		*i += 2;
	}
	else if (f[0] == DIR_CODE)
	{
		ft_dprintf(df, "%%%d", (short)get_uint16(buff, *i));
		*i += 2;
	}
	ft_dprintf(df, "\n");
}
