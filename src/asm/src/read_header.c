/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:30:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/03/14 21:59:18 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <op.h>
#include <asm.h>
#include "libft.h"

static void		fill_name(t_asm *data, char *name)
{
	int			name_len;
	int			i;

	i = 0;
	while (is_one_of(name[i], " \t"))
		i++;
	if (name[i] != 042)
		ft_exit_err("wrong syntax need \"", data);
	i++;
	if (name[i] == '\0')
		ft_exit_err("unexpected EOL", data);
	if ((name_len = ft_strchri(name + i, 042)) == -1)
		ft_exit_err("wrong syntax missing a \"", data);
	if ((name_len == 0) || name_len > 128)
		ft_exit_err("name cannot be empty or > 128", data);
	if (!empty(name + i + name_len + 1))
		ft_exit_err("line must only contain one info", data);
	if (data->header.prog_name[0] != '\0')
		ft_exit_err("name already set", data);
	ft_memcpy(data->header.prog_name, name + i, name_len);
}

static void		fill_comment(t_asm *data, char *comment)
{
	int			comment_len;
	int			i;

	i = 0;
	while (is_one_of(comment[i], " \t"))
		i++;
	if (comment[i] != 042)
		ft_exit_err("wrong syntax need \"", data);
	i++;
	if (comment[i] == '\0')
		ft_exit_err("unexpected EOL", data);
	if ((comment_len = ft_strchri(comment + i, 042)) == -1)
		ft_exit_err("wrong syntax missing a \"", data);
	if ((comment_len == 0) || comment_len > 2048)
		ft_exit_err("comment cannot be empty or > 2048", data);
	if (!empty(data->header.comment))
		ft_exit_err("already seen this", data);
	if (!empty(comment + i + comment_len + 1))
		ft_exit_err("line must only contain one info", data);
	if (data->header.comment[0] != '\0')
		ft_exit_err("comment already set", data);
	ft_memcpy(data->header.comment, comment + i, comment_len);
}

void			read_name_comment(int fd, t_asm *data)
{
	int		ret;
	char	*line;
	int		i;

	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		data->line++;
		data->column = 1;
		if (!empty(remove_comment(line)))
			break ;
		ft_strdel(&line);
	}
	if (ret < 1)
		ft_exit_err("End of file", data);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strnequ(line + i, ".name", 5))
		fill_name(data, line + i + 5);
	else if (ft_strnequ(line + i, ".comment", 8))
		fill_comment(data, line + i + 8);
	else
		ft_exit_err("no name or comment 1", data);
	ft_strdel(&line);
}

void			read_header(t_asm *data, int fd)
{
	int		a;

	a = swap_bits(0xea83f3);
	read_name_comment(fd, data);
	read_name_comment(fd, data);
	ft_cpy_buf((unsigned char *)&a, data, 4);
	ft_cpy_buf((unsigned char *)data->header.prog_name, data, PROG_NAME_LENGTH
	+ 1);
	ft_cpy_buf((unsigned char *)"\0\0\0", data, 3);
	ft_cpy_buf((unsigned char *)"\0\0\0\0", data, 4);
	ft_cpy_buf((unsigned char *)data->header.comment, data, COMMENT_LENGTH + 1);
	ft_cpy_buf((unsigned char *)"\0\0\0", data, 3);
}
