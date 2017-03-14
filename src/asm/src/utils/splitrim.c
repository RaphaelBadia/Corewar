/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitrim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 18:57:52 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/22 19:01:08 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include "op.h"

/*
** fonction qui splitte par ',' et qui vire les espaces au debut et a la fin
** de chaque parametre.
*/

char	**splitrim(char *str, t_asm *data)
{
	char	**split;
	char	*trimmed;
	int		i;

	if (!(split = ft_strsplit(str, ',')))
		ft_exit_err("Hum, caca.", data);
	i = 0;
	while (split[i])
	{
		if (!(trimmed = ft_strtrim(split[i])))
			ft_exit_err("42", data);
		if (!ft_strequ(split[i], trimmed))
		{
			free(split[i]);
			split[i] = trimmed;
		}
		i++;
	}
	return (split);
}
