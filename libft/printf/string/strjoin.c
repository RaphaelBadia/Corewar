/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 02:58:52 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/03 03:00:40 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_.h"

char		*strjoin_(char const *s1, char const *s2)
{
	char	*joinstr;

	joinstr = strnew_(strlen_(s1) + strlen_(s2));
	if (joinstr == NULL)
		return (NULL);
	return (strcat_(strcat_(joinstr, s1), s2));
}
