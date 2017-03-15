/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 22:16:49 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/15 22:08:07 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*remove_comment(char *str)
{
	char	*start_comment;

	if ((start_comment = ft_strchr(str, '#')) != NULL)
		*start_comment = '\0';
	if ((start_comment = ft_strchr(str, ';')) != NULL)
		*start_comment = '\0';
	return (str);
}

char	*remove_comment_header(char *str)
{
	char	*start_comment;
	char	*tmp;

	if ((start_comment = ft_strchr(str, '\"')) != NULL)
	{
		tmp = start_comment;
		while (tmp != str - 1)
		{
			if (*tmp == '#' || *tmp == ';')
			{
				*tmp = '\0';
				return (str);
			}
			tmp--;
		}
		if ((start_comment = ft_strchr(start_comment + 1, '\"')) != NULL)
		{
			remove_comment(start_comment + 1);
		}
	}
	else
		return (remove_comment(str));
	return (str);
}
