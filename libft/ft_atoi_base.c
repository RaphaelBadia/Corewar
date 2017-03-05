/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:54:26 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 18:55:48 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_base(char c)
{
	if (c <= '9')
		return (c - '0');
	if (c <= 'Z')
		return (c - 'A' + 10);
	if (c <= 'z')
		return (c - 'a' + 10);
	return (-1);
}

int			ft_atoi_base(const char *str, int base)
{
	int	result;
	int	sign;
	int	power;

	result = 0;
	if (PROTECT_PARAMS && (str == NULL || base <= 0))
		return (0);
	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		sign = (*str == '-' ? -1 : 1);
		str++;
	}
	power = ft_strlen(str) - 1;
	while (ft_isdigit(*str) && (power + 1) > 0)
	{
		result += get_base(*str) * ft_pow(base, power);
		str++;
		power--;
	}
	return (sign == -1 ? -result : result);
}
