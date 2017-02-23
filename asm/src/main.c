/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 14:16:59 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/23 18:53:59 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "ft_printf.h"
#include "op.h"

t_op	g_ops[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, &op_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, &op_nothing},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, &op_nothing},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, &op_nothing},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, &op_nothing},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, &op_and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, &op_nothing},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, &op_nothing},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, &op_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, &op_nothing},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, &op_sti},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, &op_nothing},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, &op_nothing},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, &op_nothing},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, &op_nothing},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, &op_nothing},
	{0, 0, {0}, 0, 0, 0, 0, 0, &op_nothing}
};

int		usage(char *prog_name)
{
	ft_printf("Usage: %s [-a] <sourcefile.s>\n    -a : Instead of ", prog_name);
	ft_printf("creating a .cor file, outputs a stripped and annotated version");
	ft_printf(" of the code to the standard output\n");
	return (1);
}

int		main(int ac, char **av)
{
	t_asm	data;
	int		fd;

	data.to_fill = NULL;
	data.knowns = NULL;
	data.line = 1;
	data.column = 1;
	data.buffer = (unsigned char *)ft_strnew(42);
	data.buff_index = 0;
	data.buff_len = 42;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		ft_exit_err("open error", &data);
	ft_bzero(data.header.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(data.header.comment, COMMENT_LENGTH + 1);
	if (ac < 2)
		return (usage(av[0]));
	read_header(&data, fd);
	read_program(&data, fd);
	int diff = data.buff_index - PROG_INSTRUCTS_START;
	data.buffer[4 + PROG_NAME_LENGTH + 1 + 3] = diff >> 24 & 0xff;
	data.buffer[4 + PROG_NAME_LENGTH + 1 + 3 + 1] = diff >> 16 & 0xff;
	data.buffer[4 + PROG_NAME_LENGTH + 1 + 3 + 2] = diff >> 8 & 0xff;
	data.buffer[4 + PROG_NAME_LENGTH + 1 + 3 + 3] = diff & 0xff;
	write(2, data.buffer, data.buff_index);
	return (0);
}
