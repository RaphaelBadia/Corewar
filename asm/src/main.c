/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:16:59 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/25 20:52:18 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <op.h>
#include <stdlib.h>

t_op		g_ops[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, &op_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, &op_ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, &op_st},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, &op_add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, &op_sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, &op_and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, &op_or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, &op_xor},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, &op_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, &op_ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, &op_sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, &op_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, &op_lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, &op_lldi},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, &op_lfork},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, &op_aff},
	{0, 0, {0}, 0, 0, 0, 0, 0, &op_nothing}
};

int			usage(char *prog_name)
{
	ft_printf("Usage: %s [-a] <sourcefile.s>\n    -a : Instead of ", prog_name);
	ft_printf("creating a .cor file, outputs a stripped and annotated version");
	ft_printf(" of the code to the standard output\n");
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

int			open_source(char *source_file)
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

void		create_cor(char *source_file, t_asm data)
{
	int		fd;
	int		n;
	char	*cor_name;

	n = ft_strlen(source_file);
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
}

void	free_lst(t_label *lst)
{
	t_label		*tmp;
	t_label		*tmp_next;

	tmp = lst;
	while(tmp)
	{
		tmp_next = tmp->next;
		free(tmp->label_name);
		free(tmp);
		tmp = tmp_next;
	}
}

int			main(int ac, char **av)
{
	t_asm	data;
	int		fd;

	if (ac != 2)
	{
		ft_putstr("Usage: ./asm <sourcefile.s>\n");
		exit(1);
	}
	if (ac < 2)
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
