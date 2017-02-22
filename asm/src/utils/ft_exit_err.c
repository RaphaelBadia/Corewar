/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 20:19:42 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/22 13:35:39 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "op.h"
#include "ft_printf.h"

void	ft_exit_err(char *msg, t_asm *data)
{
	int	save_errno;

	save_errno = errno;
	if (errno == 0)
	{
		ft_printf("syntax error: %s at [%d, %d]\n", msg, data->line,
				data->column);
	}
	else
	{
		ft_printf("system error: %s. Error message: %s\n", msg,
				strerror(save_errno));
	}
	exit(1);
}
