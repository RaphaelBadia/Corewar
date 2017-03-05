/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 18:04:37 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:05:26 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_realloc(char *str, size_t size)
{
	char	*ret;
	size_t	i;

	if (PROTECT_PARAMS && (str == NULL || size <= 0))
		return (NULL);
	i = 0;
	ret = NULL;
	if ((ret = malloc(size)) == NULL)
		return (NULL);
	ft_strncpy(ret, str, size);
	free(str);
	return (ret);
}
