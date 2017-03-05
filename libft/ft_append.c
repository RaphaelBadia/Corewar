/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:23:53 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:25:13 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** append - Add a character to an array
**
** Returns a concanetation of the string received with the character received.
**
** @return (char *) new_str
** @onFail return (NULL)
*/

char	*ft_append(char *origin, char add)
{
	char	*str;
	int		len;

	if (PROTECT_PARAMS && origin == NULL)
		return (NULL);
	len = ft_strlen(origin);
	str = ft_realloc(origin, len + 2);
	if (str == NULL)
		return (NULL);
	str[len] = add;
	str[len + 1] = '\0';
	return (str);
}
