/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:27:03 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 16:30:51 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_.h"

void	*memset_(void *str, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = str;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (str);
}
