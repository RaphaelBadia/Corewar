/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 18:39:27 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/16 21:50:23 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef EXPLICIT_ERRORS

char	*ft_strerror(int errcode)
{
	if (errcode == 1000)
		return ("ERROR");
	if (errcode == 1001)
		return ("Unexpected empty line");
	if (errcode == 1002)
		return ("A room provided in links hasn't been defined");
	if (errcode == 1003)
		return ("The starting room is not linked to the end");
	if (errcode == 1004)
		return ("Only positive and non-zero integers are allowed for ants nb");
	return ("Unknown error");
}

#else

char	*ft_strerror(int errcode)
{
	(void)errcode;
	return ("ERROR");
}

#endif
