/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 00:00:00 by jye               #+#    #+#             */
/*   Updated: 2017/01/01 19:19:59 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*test__(unsigned long long *magic)
{
	char *cp;

	cp = (char *)magic;
	if (*cp == 0)
		return (cp);
	if (*++cp == 0)
		return (cp);
	if (*++cp == 0)
		return (cp);
	if (*++cp == 0)
		return (cp);
	if (*++cp == 0)
		return (cp);
	if (*++cp == 0)
		return (cp);
	if (*++cp == 0)
		return (cp);
	if (*++cp == 0)
		return (cp);
	return (NULL);
}

size_t		ft_strlen(const char *str)
{
	unsigned long long	*magic;
	char				*cp;

	cp = (char *)str;
	while ((unsigned long long)cp & (sizeof(*magic) - 1))
	{
		if (*cp == 0)
			return (cp - str);
		++cp;
	}
	magic = (unsigned long long *)cp;
	while (1)
	{
		if ((*magic - LBITS) & HBITS)
			if ((cp = test__(magic)))
				return (cp - str);
		++magic;
	}
}
