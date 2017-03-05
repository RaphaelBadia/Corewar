/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:26:27 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:18:31 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	re_alloc(char **str, char add)
{
	char	*ptr;
	char	*strr;
	size_t	idx;

	idx = 0;
	strr = *str;
	while (strr[idx])
		idx++;
	ptr = malloc(sizeof(char) * (idx + 2));
	if (ptr == NULL)
		return ;
	idx = 0;
	while (strr[idx])
	{
		ptr[idx] = strr[idx];
		idx++;
	}
	ptr[idx] = add;
	idx++;
	ptr[idx] = '\0';
	*str = ptr;
}

static void	printex(unsigned int nb, int base, char **str)
{
	if (nb < (unsigned int)base)
	{
		if (nb <= 9)
			re_alloc(str, (nb + '0'));
		else
			re_alloc(str, (nb + 'A' - 10));
		return ;
	}
	printex(nb / base, base, str);
	nb = nb % base;
	if (nb <= 9)
		re_alloc(str, (nb + '0'));
	else
		re_alloc(str, (nb + 'A' - 10));
}

char		*ft_uitoa_base(unsigned int value, int base)
{
	char	*str;

	if (base < 2 || base > 16)
		return (NULL);
	if ((str = malloc(sizeof(char))) == NULL)
		return (NULL);
	str[0] = '\0';
	printex(value, base, &str);
	return (str);
}
