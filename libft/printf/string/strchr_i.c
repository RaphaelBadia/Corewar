/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr_i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 14:58:48 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/02 18:45:36 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*strchr_i(const char *s, int c, int *index)
{
	const char *save;

	save = s;
	while (*s)
	{
		if (*s == c)
		{
			*index = (s - save);
			return (char *)s;
		}
		s++;
	}
	*index = -1;
	return (0);
}
