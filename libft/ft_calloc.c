/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:25:29 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:26:11 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void				*ft_calloc(unsigned int n, unsigned int size)
{
	unsigned int	i;
	unsigned int	nb;
	t_byte			*p;

	nb = n * size;
	if ((p = malloc(nb)) == NULL)
		return (NULL);
	i = 0;
	while (i < nb)
	{
		p[i] = '\0';
		i++;
	}
	return (p);
}
