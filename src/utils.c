/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 20:12:20 by jye               #+#    #+#             */
/*   Updated: 2017/03/05 18:45:03 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mighty.h"
#include <stdio.h>
#include <unistd.h>

// # define GET_UINT32(buff, i)					\
// 	((*(buff + i) << 24) |						\
// 	 (*(buff + i + 1) << 16) |					\
// 	 (*(buff + i + 2) << 8) |					\
// 	 (*(buff + i + 3)))
// # define GET_UINT16(buff, i)					\
// 	((*(buff + i) << 8) |						\
// 	 (*(buff + i + 1)))

void				print32(char *str, int df, unsigned char *buff, int linereturn)
{
	int val;

	if (str)
		ft_putstr_fd(df, str);
	val = (*buff << 24) | (buff[1] << 16) | (buff[2] << 8) | (buff[3]);
	ft_putnbr_fd(df, val);
	if (linereturn)
		write(df, "\n", 1);
}

void				print16(char *str, int df, unsigned char *buff, int linereturn)
{
	short val;

	if (str)
		ft_putstr_fd(df, str);
	val = (buff[0] << 8) | (buff[1]);
	ft_putnbr_fd(df, val);
	if (linereturn)
		write(df, "\n", 1);
}

void				print8(char *str, int df, int val)
{
	if (str)
		ft_putstr_fd(df, str);
	ft_putnbr_fd(df, val);
}


void				live(unsigned char *buff, size_t *i, int df)
{
	print32("\tlive %", df, buff + *i, 0);
	(*i) += 4;
	ft_putstr_fd(df, "\n");
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
		print32("\tld %", df, buff + *i, 0);
		(*i) += 4;
	}
	else
	{
		print16("\tld ", df, buff + *i, 0);
		(*i) += 2;
	}
	ft_putstr_fd(df, ", r");
	ft_putnbr_fd(df, *(buff + *i));
	ft_putchar_fd(df, '\n');
	(*i) += 1;
}

void	st(unsigned char *buff, size_t *i, int df)
{
	unsigned char f,s;

	f = *(buff + *i) >> 6;
	s = (*(buff + *i) >> 4) & 3;
	*i += 1;
	ft_putstr_fd(df, ", r");
	dprintf(df, "\tst r%d,", *(buff + *i));
	*i += 1;
	if (s == IND_CODE)
	{
		print16(" ", df, buff + *i, 0);
		*i += 2;
	}
	else
	{
		dprintf(df, " r%d\n", *(buff + *i));
		*i += 1;
	}
	ft_putchar_fd(df, '\n');
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
			print16(NULL, df, buff + *i, 0);
			// dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			print32("%", df, buff + *i, 0);
			// dprintf(df, "%%%d", GET_UINT32(buff, *i));
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
			print16(NULL, df, buff + *i, 0);
			// dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			print32("%", df, buff + *i, 0);
			// dprintf(df, "%%%d", GET_UINT32(buff, *i));
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
			dprintf(df, "r%hhd", *(buff + *i));
			*i += 1;
			break ;
		case IND_CODE:
			print16(NULL, df, buff + *i, 0);
			// dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			print32("%", df, buff + *i, 0);
			// dprintf(df, "%%%d", GET_UINT32(buff, *i));
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
	print16("\tzjmp %", df, buff + *i, 0);
	// dprintf(df, "\tzjmp %%%hd\n", (short)GET_UINT16(buff, *i));
	*i += 2;
}

void	ldi(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	dprintf(df, "\tldi ");
	for (int d = 0; d < 3; d++)
	{
		switch (f[d])
		{
		case REG_CODE:
			dprintf(df, "r%hhd", *(buff + *i));
			*i += 1;
			break ;
		case IND_CODE:
			print16(NULL, df, buff + *i, 0);
			// dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			print16("%", df, buff + *i, 0);
			*i += 2;
			break ;
		default:
			break ;
		}
		if (d < 2)
			dprintf(df, ", ");
	}
	dprintf(df, "\n");
}

void	sti(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	dprintf(df, "\tsti ");
	for (int d = 0; d < 3; d++)
	{
		switch (f[d])
		{
		case REG_CODE:
			print8("r", df, *(buff + *i));
			*i += 1;
			break ;
		case IND_CODE:
			print16(NULL, df, buff + *i, 0);
			*i += 2;
			break ;
		case DIR_CODE:
			print16("%", df, buff + *i, 0);
			*i += 2;
			break ;
		default:
			break ;
		}
		if (d < 2)
			dprintf(df, ", ");
	}
	dprintf(df, "\n");
}

void	frk(unsigned char *buff, size_t *i, int df)
{
	// dprintf(df, "\tfork %%%hd", (short)GET_UINT16(buff, *i));
	print16("\tfork %", df, buff + *i, 0);
	*i += 2;
	dprintf(df, "\n");
}

void	lld(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	dprintf(df, "\tlld ");
	for (int d = 0; d < 2; d++)
	{
		switch (f[d])
		{
		case REG_CODE:
			dprintf(df, "r%hhd", *(buff + *i));
			*i += 1;
			break ;
		case IND_CODE:
			print16(NULL, df, buff + *i, 0);
			// dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			print32("%", df, buff + *i, 0);
			// dprintf(df, "%%%d", GET_UINT32(buff, *i));
			*i += 4;
			break ;
		default:
			break ;
		}
		if (d < 1)
			dprintf(df, ", ");
	}
	dprintf(df, "\n");
}

void	lldi(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	dprintf(df, "\tlldi ");
	for (int d = 0; d < 3; d++)
	{
		switch (f[d])
		{
		case REG_CODE:
			dprintf(df, "r%hhd", *(buff + *i));
			*i += 1;
			break ;
		case IND_CODE:
			print16(NULL, df, buff + *i, 0);
			// dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
			*i += 2;
			break ;
		case DIR_CODE:
			print16("%", df, buff + *i, 0);
			*i += 2;
			break ;
		default:
			break ;
		}
		if (d < 2)
			dprintf(df, ", ");
	}
	dprintf(df, "\n");
}

void	lfork(unsigned char *buff, size_t *i, int df)
{
	print16("\tlfork %", df, buff + *i, 0);
	// dprintf(df, "\tlfork %%%hd", (short)GET_UINT16(buff, *i));
	*i += 2;
	dprintf(df, "\n");
}

void	aff(unsigned char *buff, size_t *i, int df)
{
	char f[3];

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	dprintf(df, "\taff ");
	switch (f[0])
	{
	case REG_CODE:
		dprintf(df, "r%hhd", *(buff + *i));
		*i += 1;
		break ;
	case IND_CODE:
		print16(NULL, df, buff + *i, 0);
		// dprintf(df, "%hd", (short)GET_UINT16(buff, *i));
		*i += 2;
		break ;
	case DIR_CODE:
		print16("%", df, buff + *i, 0);
		*i += 2;
		break ;
	default:
		break ;
	}
	dprintf(df, "\n");
}
