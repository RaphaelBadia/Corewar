/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:27:17 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:27:38 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** empty
**
** Returns the original str if the string is not empty, or NULL if it is.
**
** @return true / false
*/

int		ft_isempty(char *str)
{
	if (PROTECT_PARAMS && str == NULL)
		return (1);
	while (*str)
	{
		if (!ft_isblank(*str))
			return (0);
		str++;
	}
	return (1);
}
