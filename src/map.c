/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 21:02:03 by jye               #+#    #+#             */
/*   Updated: 2017/03/09 21:03:02 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "vm.h"

void	set_map(t_vm *vm)
{
	unsigned int	i;
	unsigned int	offset;

	offset = 0;
	i = 0;
	while (i < vm->nb_player)
	{
		memcpy(vm->map + offset, vm->champ[i].byte_code, vm->champ[i].size);
		offset += MEM_SIZE / vm->nb_player;
		++i;
	}
}
