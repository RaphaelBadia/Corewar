/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 20:52:46 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 21:45:28 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "string_.h"

/*
** Not the same behavior as the real puts !!
** writes a string and returns its length
*/

int		puts_(const char *s)
{
	return (write(1, s, strlen_(s)));
}
