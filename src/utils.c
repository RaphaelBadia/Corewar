/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:12:20 by jye               #+#    #+#             */
/*   Updated: 2017/02/20 22:19:04 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mighty.h"
#include <stdio.h>
# define GET_UINT32(buff, i)					\
	((*(buff + i) << 24) |						\
	 (*(buff + i + 1) << 16) |					\
	 (*(buff + i + 2) << 8) |					\
	 (*(buff + i + 3)))
# define GET_UINT16(buff, i)					\
	((*(buff + i) << 8) |						\
	 (*(buff + i + 1)))

void	live(unsigned char *buff, size_t *i, int df)
{
	dprintf(df, "\tlive %%%d\n", GET_UINT32(buff, *i));
	(*i) += 4;
}

void	ld(unsigned char *buff, size_t *i, int df)
{
	unsigned char f,s;

	f = *(buff + *i) >> 6;
	s = (*(buff + *i) >> 4) & 3;
	(*i) += 1;
	if (f == DIR_CODE)
	{
		dprintf(df, "\tld %%%d,", GET_UINT32(buff, *i));
		(*i) += 4;
	}
	else
	{
		dprintf(df, "\tld %d,", GET_UINT16(buff, *i));
		(*i) += 2;
	}
	dprintf(df, " r%u\n", *(buff + *i));
	(*i) += 1;
}

void	st(unsigned char *buff, size_t *i, int df)
{
	unsigned char f,s;

	f = *(buff + *i) >> 6;
	s = (*(buff + *i) >> 4) & 3;
	*i += 1;
	dprintf(df, "\tst r%d,", *(buff + *i));
	*i += 1;
	if (s == IND_CODE)
	{
		dprintf(df, " %d\n", GET_UINT16(buff, *i));
		*i += 2;
	}
	else
	{
		dprintf(df, " r%d\n", *(buff + *i));
		*i += 1;
	}
}
void	add(unsigned char *buff, size_t *i, int df)
{
	*i += 1;
	dprintf(df, "\tadd r%d, r%d, r%d\n", *(buff + *i), *(buff + *i + 1), *(buff + *i + 2));
	*i += 3;
}

void	sub(unsigned char *buff, size_t *i, int df)
{
	*i += 1;
	dprintf(df, "\tsub r%d, r%d, r%d\n", *(buff + *i), *(buff + *i + 1), *(buff + *i + 2));
	*i += 3;
}

void	and(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	dprintf(df, "\tand ");
	for (int d = 0; d < 3; d++)
	{
		switch (f[d])
		{
		case REG_CODE:
			dprintf(df, "r%hhd", *(buff + *i));
			*i += 1;
			break ;
		case IND_CODE:
			dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			dprintf(df, "%%%d", GET_UINT32(buff, *i));
			*i += 4;
			break ;
		default:
			break ;
		}
		if (d < 2)
			dprintf(df, ", ");
	}
	dprintf(df, "\n");
}

void	or(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	dprintf(df, "\tor ");
	for (int d = 0; d < 3; d++)
	{
		switch (f[d])
		{
		case REG_CODE:
			dprintf(df, "r%hhd", *(buff + *i));
			*i += 1;
			break ;
		case IND_CODE:
			dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			dprintf(df, "%%%d", GET_UINT32(buff, *i));
			*i += 4;
			break ;
		default:
			break ;
		}
		if (d < 2)
			dprintf(df, ", ");
	}
	dprintf(df, "\n");
}

void	xor(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	dprintf(df, "\txor ");
	for (int d = 0; d < 3; d++)
	{
		switch (f[d])
		{
		case REG_CODE:
			dprintf(df, "r%d", *(buff + *i));
			*i += 1;
			break ;
		case IND_CODE:
			dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			dprintf(df, "%%%d", GET_UINT32(buff, *i));
			*i += 4;
			break ;
		default:
			break ;
		}
		if (d < 2)
			dprintf(df, ", ");
	}
	dprintf(df, "\n");
}

void	zjump(unsigned char *buff, size_t *i, int df)
{
	dprintf(df, "\tzjmp %%%hd\n", (short)GET_UINT16(buff, *i));
	*i += 2;
}

void	ldi(unsigned char *buff, size_t *i, int df)
{
	/* char f[3]; */

	/* f[0] = *(buff + *i) >> 6; */
	/* f[1] = (*(buff + *i) >> 4) & 3; */
	/* f[2] = (*(buff + *i) >> 2) & 3; */
	/* *i += 1; */
	/* dprintf(df, "\tand "); */
	/* for (int d = 0; d < 3; d++) */
	/* { */
	/* 	switch (f[d]) */
	/* 	{ */
	/* 	case REG_CODE: */
	/* 		dprintf(df, "r%d", *(buff + *i)); */
	/* 		*i += 1; */
	/* 		break ; */
	/* 	case IND_CODE: */
	/* 		dprintf(df, "%d", GET_UINT16(buff, *i)); */
	/* 		*i += 2; */
	/* 		break ; */
	/* 	case DIR_CODE: */
	/* 		dprintf(df, "%%%d", GET_UINT32(buff, *i)); */
	/* 		*i += 4; */
	/* 		break ; */
	/* 	default: */
	/* 		break ; */
	/* 	} */
	/* 	if (d < 2) */
	/* 		dprintf(df, ", "); */
	/* } */
	/* dprintf(df, "\n");	 */
}

void	sti(unsigned char *buff, size_t *i, int df)
{
}

void	frk(unsigned char *buff, size_t *i, int df)
{
}

void	lld(unsigned char *buff, size_t *i, int df)
{
}

void	lldi(unsigned char *buff, size_t *i, int df)
{
}

void	lfork(unsigned char *buff, size_t *i, int df)
{
}

void	aff(unsigned char *buff, size_t *i, int df)
{
}
