/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 20:52:46 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/28 16:08:01 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "string_.h"

/*
** Not the same behavior as the real puts !!
** writes a string and returns its length
*/

int		puts_fd(const int fd, const char *s)
{
	return (write(fd, s, strlen_(s)));
}
