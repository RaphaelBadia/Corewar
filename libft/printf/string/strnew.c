/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnew.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:19:39 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 15:22:14 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string_.h"

char		*strnew_(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	size++;
	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	while (i < size)
		str[i++] = '\0';
	return (str);
}
