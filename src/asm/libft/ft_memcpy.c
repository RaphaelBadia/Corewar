/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:26:05 by jye               #+#    #+#             */
/*   Updated: 2016/12/10 22:11:09 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long long	*ldst;
	unsigned long long	*lsrc;
	unsigned char		*cdst;
	unsigned char		*csrc;

	cdst = (unsigned char *)dst;
	csrc = (unsigned char *)src;
	ldst = NULL;
	while (((unsigned long)cdst & (sizeof(unsigned long long) - 1)) && n)
	{
		*cdst++ = *csrc++;
		--n;
	}
	if (n >= 8)
	{
		ldst = (unsigned long long *)cdst;
		lsrc = (unsigned long long *)csrc;
		while (n >= 8 && (*ldst++ = *lsrc++))
			n -= 8;
	}
	csrc = ldst != NULL ? (unsigned char *)lsrc : csrc;
	cdst = ldst != NULL ? (unsigned char *)ldst : cdst;
	while (n-- > 0)
		*cdst++ = *csrc++;
	return (dst);
}
