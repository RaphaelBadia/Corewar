/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:29:47 by jye               #+#    #+#             */
/*   Updated: 2017/03/11 19:23:43 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "vm.h"

void	usage(char *p_name)
{
	printf("%s: [-dump N] [-n N gladiator.cor...]\n", p_name);
	printf("########### HELP OUTPUT MODE ##############\n");
	printf("%10s Dumps the map in hexadecimal at N cycle.\n", "\t-dump N");
	printf("%10s Print the map every N cycle.\n", "\t-s N");
	printf("%10s Turn on the aff instruction (default is off).\n", "\t-a");
	printf("%10s Print information about what the fuck the vm is doing",
			"\t-v");
	printf(" (default is 0).\n");
	printf("%10s Silence VM output (cancels verbose mode).\n", "\t-q");
	exit(EXIT_FAILURE);
}
