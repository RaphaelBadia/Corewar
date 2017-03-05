/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:22:15 by rbadia            #+#    #+#             */
/*   Updated: 2016/11/10 16:30:42 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*trimstr;
	size_t	i;
	size_t	len;

	if (PROTECT_PARAMS && s == NULL)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (ft_strnew(0));
	len = ft_strlen(s) - 1;
	while (len > 0 && (s[len] == ' ' || s[len] == '\n' || s[len] == '\t'))
		len--;
	if (i == 0 && len == ft_strlen(s) - 1)
		return (ft_strdup(s));
	len++;
	trimstr = ft_strnew(len - i);
	if (trimstr == NULL)
		return (NULL);
	return (ft_strncpy(trimstr, (s + i), len - i));
}
