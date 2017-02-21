/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchri.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 23:21:07 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/21 23:27:31 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		ft_strchri(char *str, char c)
{
	char	*chr;

	chr = ft_strchr(str, c);
	if (chr == NULL || chr - str > INT_MAX)
		return (-1);
	return (chr - str);
}
