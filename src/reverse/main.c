/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 17:40:19 by jye               #+#    #+#             */
/*   Updated: 2017/03/17 15:04:05 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ft_printf.h>
#include <reverse.h>
#include <op.h>

int					open_output(char *name)
{
	int				fd;
	char			*ext;

	if (!(ext = malloc(ft_strlen(name) + 5)))
		ft_exit("Malloc failure");
	ft_strcpy(ext, name);
	ft_strcat(ext, EXT);
	if (-1 == (fd = open(ext, O_WRONLY | O_CREAT | O_TRUNC, 0666)))
		ft_exit(strerror(errno));
	free(ext);
	return (fd);
}

unsigned char		*open_binary_get_buffer(t_disassembly *dasm, char *name)
{
	unsigned char	*ret;

	if (-1 == (dasm->binary_fd = open(name, O_RDONLY)))
		ft_exit(strerror(errno));
	if (!(ret = malloc(sizeof(char) * (BUFF + 1))))
		ft_exit(strerror(errno));
	ft_bzero(ret, sizeof(char) * (BUFF + 1));
	if ((dasm->file_size = read(dasm->binary_fd, ret, BUFF)) <= 0)
		ft_exit("problem reading file");
	if (dasm->file_size == BUFF)
		ft_exit("The file is too big.");
	return (ret);
}

void				read_header(t_disassembly *dasm, unsigned char *buff,
																	char *pname)
{
	if (!(dasm->prog_name = malloc(129)))
		ft_exit(strerror(errno));
	ft_memcpy(dasm->prog_name, buff + dasm->byte, 128);
	dasm->prog_name[128] = 0;
	dasm->byte += 132;
	dasm->prog_size = (buff[dasm->byte + 2] << 8) | *(buff + dasm->byte + 3);
	dasm->byte += 4;
	dasm->prog_comment = malloc(2049);
	ft_memcpy(dasm->prog_comment, buff + dasm->byte, 2048);
	dasm->byte += 2052;
	dasm->output_fd = open_output(pname);
	ft_dprintf(dasm->output_fd, ".name \"%s\"\n", dasm->prog_name);
	ft_dprintf(dasm->output_fd, ".comment \"%s\"\n\n", dasm->prog_comment);
	free(dasm->prog_name);
	free(dasm->prog_comment);
}

void				show_instruction(t_disassembly *dasm, unsigned char *buff)
{
	int				j;
	static void		(*f[])() = {NULL, &live, &ld, &st, &add, &sub, &and,
								&or, &xor, &zjump, &ldi, &sti, &frk, &lld,
								&lldi, &lfork, &aff};

	j = 0;
	while (j < 16 && g_op_tab[j].opcode != buff[dasm->byte])
		j++;
	dasm->byte += 1;
	if (j < 16)
		f[j](buff, &dasm->byte, dasm->output_fd);
	else
		ft_printf("shit, i didnt find the function to use for %x %lu %d!\n",
		buff[dasm->byte - 1], dasm->file_size - dasm->byte, j);
}

int					main(int ac, char **av)
{
	t_disassembly	dasm;
	unsigned char	*buff;
	int				i;

	if (ac < 2)
	{
		ft_dprintf(2, "dasm: disassemble a compiled .cor file.\n");
		ft_dprintf(2, "usage: %s [file ...]\n", av[0]);
		return (1);
	}
	i = 0;
	while (++i < ac)
	{
		ft_printf("Reversing %s... \n", av[i]);
		dasm.byte = 4;
		buff = open_binary_get_buffer(&dasm, av[i]);
		if (*(unsigned int *)buff != MAGIC)
			ft_exit("Bad magic number");
		read_header(&dasm, buff, av[i]);
		while (dasm.byte < (size_t)dasm.file_size)
			show_instruction(&dasm, buff);
		free(buff);
	}
	ft_printf("Done !\n");
	return (0);
}
