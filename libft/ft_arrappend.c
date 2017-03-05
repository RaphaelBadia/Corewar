/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 19:32:19 by raphael           #+#    #+#             */
/*   Updated: 2017/02/02 19:40:54 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	**ft_arrappend(char **arr, char *add)
{
	char	**new_arr;
	size_t	i;

	if ((new_arr = malloc(sizeof(char *) * (ft_arrlen(arr) + 2))) == NULL)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		new_arr[i] = arr[i];
		++i;
	}
	new_arr[i] = add;
	++i;
	new_arr[i] = NULL;
	free(arr);
	return (new_arr);
}
