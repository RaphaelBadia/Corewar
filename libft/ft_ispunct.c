/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 12:53:48 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 11:58:52 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ref: http://www.cplusplus.com/reference/cctype/
*/

int		ft_ispunct(int c)
{
	return (ft_isprint(c) && !ft_isblank(c) && !ft_isalnum(c));
}
