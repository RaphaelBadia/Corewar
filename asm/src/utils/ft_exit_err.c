/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:19:42 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/21 23:44:43 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ft_printf.h"

void	ft_exit_err(char *msg, int line, int colomn)
{
	perror(msg);
	ft_printf("at [%d, %d]", line, colomn);
	exit(1);
}
