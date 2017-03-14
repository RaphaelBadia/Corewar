/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:16:59 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/14 19:07:54 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <op.h>
#include <asm.h>
#include <stdlib.h>

int			usage(char *prog_name)
{
	ft_printf("Usage: %s <sourcefile.s>\n", prog_name);
	return (1);
}

static void	program_size(t_asm *data)
{
	int		diff;

	diff = data->buff_index - PROG_INSTRUCTS_START;
	data->buffer[4 + PROG_NAME_LENGTH + 1 + 3] = diff >> 24 & 0xff;
	data->buffer[4 + PROG_NAME_LENGTH + 1 + 3 + 1] = diff >> 16 & 0xff;
	data->buffer[4 + PROG_NAME_LENGTH + 1 + 3 + 2] = diff >> 8 & 0xff;
	data->buffer[4 + PROG_NAME_LENGTH + 1 + 3 + 3] = diff & 0xff;
}

static int	open_source(char *source_file)
{
	int		fd;
	int		n;

	n = ft_strlen(source_file);
	if ((n < 2) || (source_file[n - 2] != '.') || (source_file[n - 1] != 's'))
	{
		ft_putstr("Usage: ./asm <sourcefile.s>\n");
		exit(1);
	}
	if ((fd = open(source_file, O_RDONLY)) == -1)
		ft_exit_err("open error", NULL);
	return (fd);
}

static void	create_cor(char *source_file, t_asm data)
{
	int		fd;
	int		n;
	char	*cor_name;

	n = ft_strlen(source_file);
	if (data.buff_index == 2192)
		ft_exit_err("no source code", &data);
	if (!(cor_name = ft_strnew(n + 2)))
		ft_exit_err("malloc error", &data);
	ft_strcpy(cor_name, source_file);
	cor_name[n - 1] = 'c';
	cor_name[n] = 'o';
	cor_name[n + 1] = 'r';
	fd = open(cor_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	write(1, "Writing output program to ", 26);
	ft_putstr(cor_name);
	write(1, "\n", 1);
	write(fd, data.buffer, data.buff_index);
	free(cor_name);
}

int			main(int ac, char **av)
{
	t_asm	data;
	int		fd;

	if (ac != 2)
		return (usage(av[0]));
	data.to_fill = NULL;
	data.knowns = NULL;
	data.line = 1;
	data.column = 1;
	if (!(data.buffer = (unsigned char *)ft_strnew(42)))
		ft_exit_err("malloc error", &data);
	data.buff_index = 0;
	data.buff_len = 42;
	fd = open_source(av[1]);
	ft_bzero(data.header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(data.header.comment, COMMENT_LENGTH + 1);
	read_header(&data, fd);
	read_program(&data, fd);
	program_size(&data);
	create_cor(av[1], data);
	free_lst(data.knowns);
	free_lst(data.to_fill);
	free(data.buffer);
	return (0);
}
