/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_buf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 21:25:13 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/22 17:04:35 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdlib.h>
#include "libft.h"

void	ft_realoc(t_asm *data, size_t n)
{
	unsigned char	*tmp;

	tmp = data->buffer;
	if (!(data->buffer = ft_memalloc(sizeof(char) * n)))
		return ;
	ft_memcpy(data->buffer, tmp, data->buff_index);
	free(tmp);
	data->buff_len += BUFFSIZE;
}

void	ft_cpy_buf(unsigned char *str, t_asm *data, size_t n)
{
	unsigned char	*dest;

	if (str == NULL)
		return ;
	dest = data->buffer + data->buff_index;
	if ((data->buff_index + n) >= data->buff_len)
	{
		ft_realoc(data, data->buff_len + BUFFSIZE);
		ft_cpy_buf(str, data, n);
		return ;
	}
	ft_memcpy(dest, str, n);
	data->buff_index += n;
}
