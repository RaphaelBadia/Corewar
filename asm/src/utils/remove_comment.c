/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:16:49 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/23 22:27:19 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*remove_comment(char *str)
{
	char	*start_comment;

	if ((start_comment = ft_strchr(str, '#')) != NULL)
		*start_comment = '\0';
	return (str);
}
