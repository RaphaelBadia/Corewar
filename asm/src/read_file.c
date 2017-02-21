/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <vcombey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:30:10 by vcombey           #+#    #+#             */
/*   Updated: 2017/02/21 22:54:37 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "op.h"
#include "libft.h"

static void		fill_name(char *name, t_asm *data)
{
	char		*tmp;
	int			i;

	i = 0;
	while (is_one_of(name[i], " \t"))
		i++;
	if (name[i] != 042) // c est un "
		ft_exit_err("wrong syntax need \"");
	i++;
	if (name[i] == '\0')
		ft_exit_err("unexpected EOL");
	if ((tmp = ft_strchr(name + i, 042)) == NULL)
		ft_exit_err("wrong syntax missing a \"");
	if (tmp - (name + i) <= 0 || tmp - (name + i) > 128)
		ft_exit_err("name cannot be empty or > 128");
	ft_strncpy(data->header.prog_name, name + i, tmp - name);
}

int			read_name(int fd, t_asm *data)
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
		fill_name(data, line + i);
	if (ft_strnequ(line + i, ".comment:", 9))
		fill_comment(data, line);

}

void		read_file(char *filename, t_asm *data)
{
	int		fd;
	int		ret;

	data->buffer = NULL;
	if ((fd = open(filename, O_RDONLY)) == -1)
		ft_exit_err("open");
	if (!(ret = read_name(fd, data)))
		ft_exit_err("wrong name");
}
