/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putsprintable_n_buf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 20:52:46 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/05 10:53:37 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "string_.h"
#include "stdio_.h"

static int		is_printable(const unsigned char c)
{
	return (32 <= c && c <= 127);
}

static void		putnbrbase_secret(uintmax_t nb, char *b, t_pf *data)
{
	uintmax_t	blen;

	blen = strlen_(b);
	if (nb >= blen)
	{
		putnbrbase_secret(nb / blen, b, data);
		putnbrbase_secret(nb % blen, b, data);
	}
	else
		buffwrite_c(data, b[nb]);
}

int				putsprintable_n_buf(t_pf *data, unsigned char *s, size_t n)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (i < n)
	{
		if (is_printable(s[i]))
		{
			buffwrite_c(data, s[i]);
			count++;
		}
		else
		{
			buffwrite_c(data, '\\');
			count += nbrbase_len(s[i], "0123456789") + 1;
			putnbrbase_secret((int)s[i], "0123456789", data);
		}
		i++;
	}
	return (count);
}
