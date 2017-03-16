/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 21:47:22 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/16 17:43:54 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <mighty.h>

void				and(unsigned char *buff, size_t *i, int df)
{
	char	f[3];
	int		d;

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	ft_dprintf(df, "\tand ");
	d = 0;
	while (d < 3)
	{
		if (f[d] == REG_CODE)
			ft_dprintf(df, "r%hhd", *(buff + *i));
		else if (f[d] == IND_CODE)
			ft_dprintf(df, "%hd", (short)get_uint16(buff, *i));
		else if (f[d] == DIR_CODE)
			ft_dprintf(df, "%%%hd", (short)get_uint32(buff, *i));
		*i += get_code_value(f[d], 1);
		if (d < 2)
			ft_dprintf(df, ", ");
		++d;
	}
	ft_dprintf(df, "\n");
}

void				or(unsigned char *buff, size_t *i, int df)
{
	char	f[3];
	int		d;

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	ft_dprintf(df, "\tor ");
	d = 0;
	while (d < 3)
	{
		if (f[d] == REG_CODE)
			ft_dprintf(df, "r%hhd", *(buff + *i));
		else if (f[d] == IND_CODE)
			ft_dprintf(df, "%hd", (short)get_uint16(buff, *i));
		else if (f[d] == DIR_CODE)
			ft_dprintf(df, "%%%hd", (short)get_uint32(buff, *i));
		*i += get_code_value(f[d], 1);
		if (d < 2)
			ft_dprintf(df, ", ");
		++d;
	}
	ft_dprintf(df, "\n");
}

void				xor(unsigned char *buff, size_t *i, int df)
{
	char	f[3];
	int		d;

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	ft_dprintf(df, "\txor ");
	d = 0;
	while (d < 3)
	{
		if (f[d] == REG_CODE)
			ft_dprintf(df, "r%hhd", *(buff + *i));
		else if (f[d] == IND_CODE)
			ft_dprintf(df, "%hd", (short)get_uint16(buff, *i));
		else if (f[d] == DIR_CODE)
			ft_dprintf(df, "%%%hd", (short)get_uint32(buff, *i));
		*i += get_code_value(f[d], 1);
		if (d < 2)
			ft_dprintf(df, ", ");
		++d;
	}
	ft_dprintf(df, "\n");
}

void				zjump(unsigned char *buff, size_t *i, int df)
{
	ft_dprintf(df, "\tzjmp %%%hd\n", (short)get_uint16(buff, *i));
	*i += 2;
}

void				ldi(unsigned char *buff, size_t *i, int df)
{
	char	f[3];
	int		d;

	f[0] = *(buff + *i) >> 6;
	f[1] = (*(buff + *i) >> 4) & 3;
	f[2] = (*(buff + *i) >> 2) & 3;
	*i += 1;
	ft_dprintf(df, "\tldi ");
	d = 0;
	while (d < 3)
	{
		if (f[d] == REG_CODE)
			ft_dprintf(df, "r%hhd", *(buff + *i));
		else if (f[d] == IND_CODE)
			ft_dprintf(df, "%hd", (short)get_uint16(buff, *i));
		else if (f[d] == DIR_CODE)
			ft_dprintf(df, "%%%hd", (short)get_uint16(buff, *i));
		*i += get_code_value(f[d], 0);
		if (d < 2)
			ft_dprintf(df, ", ");
		++d;
	}
	ft_dprintf(df, "\n");
}
