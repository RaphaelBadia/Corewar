/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nothing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 18:11:05 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/27 18:11:06 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <op.h>
#include <asm.h>
#include <stdlib.h>
#include <ft_printf.h>

void		op_nothing(t_asm *data, char **args)
{
	(void)data;
	(void)args;
	ft_printf("im not coded yet\n");
	exit(1);
	ft_arrfree(args);
}
