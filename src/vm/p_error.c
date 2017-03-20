/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 20:39:35 by jye               #+#    #+#             */
/*   Updated: 2017/03/20 19:15:39 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ft_printf.h>
#include <errno.h>
#include <stdlib.h>
#include <vm.h>

void	p_error(void)
{
	perror(ERROR);
	exit(EXIT_FAILURE);
}

void	vm_error(char *error_string)
{
	ft_printf("%s", error_string);
	exit(EXIT_FAILURE);
}
