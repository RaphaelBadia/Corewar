/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 14:22:09 by jye               #+#    #+#             */
/*   Updated: 2016/12/09 16:23:16 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned long long	init__(unsigned long long **magic,
									void *cp, unsigned char c)
{
	unsigned long long mask;

	mask = c;
	mask = (mask << 8) | mask;
	mask = (mask << 16) | mask;
	mask = ((mask << 16) << 16) | mask;
	*magic = (unsigned long long *)cp;
	return (mask);
}

char						*ft_strchr(const char *s, unsigned char c)
{
	unsigned long long	mask;
	unsigned long long	*magic;
	char				*cp;
	char				i;

	cp = (char *)s - 1;
	while ((sizeof(unsigned long long) - 1) & (unsigned long)++cp)
		if (*cp == c || *cp == 0)
			return (*cp == c ? cp : NULL);
	mask = init__(&magic, cp, c);
	while (1)
	{
		if (((*magic - LBITS) & HBITS) || (((*magic ^ mask) - LBITS) & HBITS))
		{
			cp = (char *)magic;
			i = -1;
			while (++i < 8)
				if (*cp == c)
					return (cp);
				else if (*cp++ == 0)
					return (NULL);
		}
		++magic;
	}
}
