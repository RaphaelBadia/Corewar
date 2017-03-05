/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:38:16 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/11 19:06:44 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_words(char const *str, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] == '\0')
			return (count);
		count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*dup(char const *str, char c)
{
	char	*ret;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if ((ret = malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

static char	**ft_strsplit2(char const *str, char c)
{
	char	**ret;
	size_t	i;
	size_t	str_i;
	size_t	wordcount;

	i = 0;
	str_i = 0;
	wordcount = count_words(str, c);
	if ((ret = malloc(sizeof(char *) * (wordcount + 1))) == NULL)
		return (NULL);
	while (str[str_i])
	{
		while (str[str_i] && (str[str_i] == c))
			str_i++;
		if (str[str_i] != '\0')
		{
			if ((ret[i++] = dup(&str[str_i], c)) == NULL)
				return (NULL);
		}
		while (str[str_i] && str[str_i] != c)
			str_i++;
	}
	ret[i] = NULL;
	return (ret);
}

char		**ft_strsplit(char const *str, char c)
{
	if (PROTECT_PARAMS && str == NULL)
		return (NULL);
	return (ft_strsplit2(str, c));
}
