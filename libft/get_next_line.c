/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 00:32:02 by rbadia            #+#    #+#             */
/*   Updated: 2017/01/31 18:59:13 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"

static char		*enlarge_your_buff(int const fd, char *buffer, int *ret)
{
	char		tmp[BUFF_SIZE + 1];
	char		*trash;

	*ret = read(fd, tmp, BUFF_SIZE);
	if (*ret == -1)
		return (NULL);
	tmp[*ret] = '\0';
	trash = buffer;
	buffer = ft_strjoin(buffer, tmp);
	ft_strdel(&trash);
	return (buffer);
}

static t_fd		*create_fd(void)
{
	t_fd		*new_fd;

	new_fd = malloc(sizeof(t_fd));
	if (new_fd == NULL)
		return (NULL);
	new_fd->buffer = (char *)"";
	return (new_fd);
}

static int		last_return(char *buffer, char **line, int ret)
{
	if (buffer[0] != 0)
	{
		*line = ft_strdup(buffer);
		ft_strclr(buffer);
		ret = 1;
	}
	return (ret);
}

int				get_next_line(int const fd, char **line)
{
	static t_fd	*storage[4864];
	int			ret;
	char		*next;

	if (!line || fd < 0 || fd >= 4864)
		return (-1);
	if (!storage[fd] && ((storage[fd] = create_fd()) == NULL))
		return (-1);
	ret = 1;
	if (storage[fd]->buffer[0] == '\0')
		storage[fd]->buffer = ft_strnew(0);
	while (ret > 0)
	{
		if ((next = ft_strchr(storage[fd]->buffer, '\n')) != NULL)
		{
			*next = '\0';
			*line = ft_strdup(storage[fd]->buffer);
			ft_memmove(storage[fd]->buffer, next + 1, ft_strlen(next + 1) + 1);
			return (1);
		}
		storage[fd]->buffer = enlarge_your_buff(fd, storage[fd]->buffer, &ret);
		if (!storage[fd]->buffer)
			return (-1);
	}
	return (last_return(storage[fd]->buffer, line, ret));
}
