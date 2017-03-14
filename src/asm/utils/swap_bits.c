/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_bits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:25:08 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/22 17:38:03 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		swap_bits(int integer)
{
	int	ret;

	ret = integer & 0xff;
	ret <<= 8;
	integer >>= 8;
	ret += integer & 0xff;
	ret <<= 8;
	integer >>= 8;
	ret += integer & 0xff;
	ret <<= 8;
	integer >>= 8;
	ret += integer & 0xff;
	return (ret);
}
