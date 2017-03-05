/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 16:59:42 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 18:30:55 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int		ft_upow(unsigned int nb, int power)
{
	unsigned int	result;

	if (power < 0)
		return (0);
	result = 1;
	while (power--)
		result *= nb;
	return (result);
}
