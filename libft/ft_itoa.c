/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:57:03 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:08:15 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		ft_itoa_rec(long int nbr, char *s, int *index)
{
	if (nbr > 9)
		ft_itoa_rec(nbr / 10, s, index);
	s[(*index)++] = '0' + nbr % 10;
}

char			*ft_itoa(int n)
{
	char		*str;
	char		*clean_str;
	int			index;
	long int	nbr;

	str = ft_strnew(12);
	if (str == NULL)
		return (NULL);
	index = 0;
	nbr = (long int)n;
	if (nbr < 0)
	{
		str[index] = '-';
		index++;
	}
	ft_itoa_rec(ABS(nbr), str, &index);
	str[index] = '\0';
	clean_str = ft_strdup(str);
	if (clean_str == NULL)
		return (NULL);
	free(str);
	return (clean_str);
}
