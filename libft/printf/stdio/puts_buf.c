/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 20:52:46 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 22:50:11 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "stdio_.h"

int		puts_buf(t_pf *data, const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		buffwrite_c(data, s[i]);
		i++;
	}
	return (i);
}
