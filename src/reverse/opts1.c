/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 21:46:16 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/16 17:43:50 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <mighty.h>

void				live(unsigned char *buff, size_t *i, int df)
{
	ft_dprintf(df, "\tlive %%%d\n", get_uint32(buff, *i));
	(*i) += 4;
}

void				ld(unsigned char *buff, size_t *i, int df)
{
	unsigned char	f;
	unsigned char	s;

	f = *(buff + *i) >> 6;
	s = (*(buff + *i) >> 4) & 3;
	(*i) += 1;
	if (f == DIR_CODE)
	{
		ft_dprintf(df, "\tld %%%d,", get_uint32(buff, *i));
		(*i) += 4;
	}
	else
	{
		ft_dprintf(df, "\tld %hd,", (short)get_uint16(buff, *i));
		(*i) += 2;
	}
	ft_dprintf(df, " r%u\n", *(buff + *i));
	(*i) += 1;
}

void				st(unsigned char *buff, size_t *i, int df)
{
	unsigned char	f;
	unsigned char	s;

	f = *(buff + *i) >> 6;
	s = (*(buff + *i) >> 4) & 3;
	*i += 1;
	ft_dprintf(df, "\tst r%d,", *(buff + *i));
	*i += 1;
	if (s == IND_CODE)
	{
		ft_dprintf(df, " %d\n", get_uint16(buff, *i));
		*i += 2;
	}
	else
	{
		ft_dprintf(df, " r%d\n", *(buff + *i));
		*i += 1;
	}
}

void				add(unsigned char *buff, size_t *i, int df)
{
	*i += 1;
	ft_dprintf(df, "\tadd r%d, r%d, r%d\n", *(buff + *i),
											*(buff + *i + 1),
											*(buff + *i + 2));
	*i += 3;
}

void				sub(unsigned char *buff, size_t *i, int df)
{
	*i += 1;
	ft_dprintf(df, "\tsub r%d, r%d, r%d\n", *(buff + *i),
											*(buff + *i + 1),
											*(buff + *i + 2));
	*i += 3;
}
