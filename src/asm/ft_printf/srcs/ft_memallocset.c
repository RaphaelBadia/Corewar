/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memallocset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:59:56 by jye               #+#    #+#             */
/*   Updated: 2016/12/13 19:11:30 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

void	*ft_memallocset(unsigned char c, unsigned long size)
{
	void *ret;

	if ((ret = malloc(size)) == NULL)
		return (NULL);
	ft_memset(ret, c, size);
	return (ret);
}
