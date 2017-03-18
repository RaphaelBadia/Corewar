/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 18:08:24 by jye               #+#    #+#             */
/*   Updated: 2017/03/18 18:24:25 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>
#include "graphic.h"

int		main(int ac, char **av)
{
	t_vm	vm;
	t_arg	arg;

	arg.ac = ac;
	arg.av = av;
	arg.i = 0;
	if (ac == 1)
		usage(av[0]);
	memset(&vm, 0, sizeof(t_vm));
	set_flag(&vm, &arg);
	vm.nb_player = set_champ(vm.champ, &arg);
	play(&vm);
	return (0);
}
