/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:54:26 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:26:49 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_base(char c)
{
	if (c <= '9')
		return (c - '0');
	if (c <= 'Z')
		return (c - 'A' + 10);
	if (c <= 'z')
		return (c - 'a' + 10);
	return (-1);
}

unsigned int		ft_atoui_base(const char *str, int base)
{
	unsigned int	result;
	int				power;

	if (PROTECT_PARAMS && str == NULL)
		return (0);
	result = 0;
	while (*str == ' ' || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '+')
		str++;
	power = ft_strlen(str) - 1;
	while (ft_isdigit(*str) && (power + 1) > 0)
	{
		result += get_base(*str) * ft_upow(base, power);
		str++;
		power--;
	}
	return (result);
}
