/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_explode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 19:06:15 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/12 11:00:23 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** returns an int if delimiter matches the beginning of str
** @return int
*/

static int	match_delimiter(char *str, char *delimiter)
{
	size_t	i;

	i = 0;
	if (ft_strcmp(delimiter, " ") == 0)
	{
		while (str[i] != 0 && delimiter[i] != 0 && (str[i] == delimiter[i] ||
		str[i] == '\t'))
			i++;
	}
	else
	{
		while (str[i] != 0 && delimiter[i] != 0 && str[i] == delimiter[i])
			i++;
	}
	if (delimiter[i] == 0)
		return (i);
	return (0);
}

/*
** Ignores every (char *)delimiter at the begging of the string
** by incrementing the pointer of (char *)str.
**
** Once the nexts characters are not forming the delimiter string,
** counts them as an entity (usually a word).
**
** Once a new delimiter is found, calls itself recursively.
**
** @return (int) entities_count
*/

static int	get_entities_count(char *str, char *delimiter)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (*str != 0 && match_delimiter(str, delimiter))
		str++;
	if (*str == 0)
		return (0);
	while (*str != 0 && !(i = match_delimiter(str, delimiter)))
		str++;
	str += i;
	count++;
	if (*str != 0)
		return (count + get_entities_count(str, delimiter));
	return (count);
}

/*
** gets the number of bytes between two pointers.
** @return (int) size
*/

static int	get_size_between(char *ptr1, char *ptr2)
{
	int	size;

	size = 0;
	while (ptr1 != ptr2)
	{
		size++;
		ptr1++;
	}
	return (size);
}

/*
** Has the same behavior as get_entities_count, but allocs the array
** given instead of counting how many entities there is.
**
** @return (int) entities_count
*/

static int	explode_and_fill(char *str, char *delimiter, char **array, int idx)
{
	int		i;
	int		count;
	char	*entity_beginning;

	i = 0;
	count = 0;
	while (*str != 0 && match_delimiter(str, delimiter))
		str++;
	if (*str == 0)
		return (0);
	entity_beginning = str;
	while (*str != 0 && !(i = match_delimiter(str, delimiter)))
		str++;
	if ((array[idx] = ft_calloc(get_size_between(entity_beginning, str) + 1,
	sizeof(char))) == NULL)
		return (0);
	ft_strncpy(array[idx], entity_beginning,
		get_size_between(entity_beginning, str));
	array[idx][get_size_between(entity_beginning, str)] = '\0';
	str += i;
	count++;
	if (*str != 0)
		return (count + explode_and_fill(str, delimiter, array, ++idx));
	return (count);
}

/*
** explode - Split a string by string
**
** Returns an array of strings, each of which is a substring of string
** formed by splitting it on boundaries formed by the string delimiter.
**
** @return (char **) substrings
** @onFail return (NULL)
*/

char		**ft_explode(char *str, char *delimiter)
{
	char	**array;
	int		entities_count;
	int		idx;

	entities_count = 0;
	idx = 0;
	if (str == NULL || delimiter == NULL)
		return (NULL);
	entities_count = get_entities_count(str, delimiter);
	if (entities_count == 0)
		return (NULL);
	if ((array = malloc((entities_count + 2) * sizeof(char *))) == NULL)
		return (NULL);
	while (idx < entities_count + 1)
		array[idx++] = NULL;
	if (!(explode_and_fill(str, delimiter, array, 0)))
		return (NULL);
	return (array);
}
