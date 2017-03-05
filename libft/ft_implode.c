/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_implode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 16:01:28 by raphael           #+#    #+#             */
/*   Updated: 2017/02/02 12:29:40 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_implode(char **tab, char c, size_t limit)
{
	size_t	i;
	char	*tmp;
	char	*str;

	str = NULL;
	if (limit == 1)
		return (ft_strdup(tab[0]));
	i = 1;
	if ((tmp = ft_strdup(tab[0])) == NULL)
		return (NULL);
	while (i < limit)
	{
		if ((tmp = ft_append(tmp, c)) == NULL)
			return (NULL);
		if ((str = ft_strjoin(tmp, tab[i])) == NULL)
			return (NULL);
		free(tmp);
		tmp = str;
		i++;
	}
	return (str);
}
