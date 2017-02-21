/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:30:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/21 23:45:01 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "op.h"
#include "libft.h"

static void		fill_name(t_asm *data, char *name)
{
	int			name_len;
	int			i;

	i = 0;
	while (is_one_of(name[i], " \t"))
		i++;
	if (name[i] != 042) // c est un "
		ft_exit_err("wrong syntax need \"");
	i++;
	if (name[i] == '\0')
		ft_exit_err("unexpected EOL");
	if ((name_len = ft_strchri(name + i, 042)) == -1)
		ft_exit_err("wrong syntax missing a \"");
	if ((name_len == 0) || name_len > 128)
		ft_exit_err("name cannot be empty or > 128");
	ft_memcpy(data->header.prog_name, name + i, name_len);
}

static void		fill_comment(t_asm *data, char *comment)
{
	int			comment_len;
	int			i;

	i = 0;
	while (is_one_of(comment[i], " \t"))
		i++;
	if (comment[i] != 042) // c est un "
		ft_exit_err("wrong syntax need \"");
	i++;
	if (comment[i] == '\0')
		ft_exit_err("unexpected EOL");
	if ((comment_len = ft_strchri(comment + i, 042)) == -1)
		ft_exit_err("wrong syntax missing a \"");
	if ((comment_len == 0) || comment_len > 128)
		ft_exit_err("name cannot be empty or > 128");
	ft_memcpy(data->header.comment, comment + i, comment_len);
}

void		read_name_comment(int fd, t_asm *data)
{
	int		ret;
	char	*line;
	char	**arr;
	int		i;

	while ((ret = get_next_line(fd, &line)) != 0 && empty(line))
	{
		if (ret == -1)
			ft_exit_err("EOF");
		free(line);
		data->line++;
	}
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strnequ(line + i, ".name:", 5))
		fill_name(data, line + i + 7);
	else if (ft_strnequ(line + i, ".comment:", 9))
		fill_comment(data, line + i + 10);
	else
		ft_exit_err("no name or comment");
	while ((ret = get_next_line(fd, &line)) != 0 && empty(line))
	{
		if (ret == -1)
			ft_exit_err("EOF");
		free(line);
		data->line++;
	}
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strnequ(line + i, ".comment:", 9))
		fill_comment(data, line + i + 10);
	else if (ft_strnequ(line + i, ".name:", 5))
		fill_name(data, line + i + 7);
	else
		ft_exit_err("no name or comment");
}

void		read_file(char *filename, t_asm *data)
{
	int		fd;
	int		ret;

	data->buffer = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_exit_err("open");
	read_name_comment(fd, data);
}
