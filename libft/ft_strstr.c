/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 18:34:32 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 18:42:35 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	idx;
	size_t	find_idx;

	idx = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[idx])
	{
		find_idx = 0;
		while (big[idx + find_idx] && little[find_idx]
				&& big[idx + find_idx] == little[find_idx])
			find_idx++;
		if (little[find_idx] == '\0')
			return ((char *)&big[idx]);
		idx++;
	}
	return (NULL);
}
