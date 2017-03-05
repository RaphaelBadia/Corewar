/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:20:18 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 15:23:05 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string_.h"

char	*strdup_(const char *s)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (strlen_(s) + 1));
	if (dup == NULL)
		return (NULL);
	return (strcpy_(dup, s));
}
