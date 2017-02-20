/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 17:40:19 by jye               #+#    #+#             */
/*   Updated: 2017/02/20 22:58:09 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "mighty.h"

int		add_ext(char *name)
{
	int		fd;
	char	*ext;

	ext = malloc(strlen(name) + 5);
	strcpy(ext, name);
	strcat(ext, EXT);
	fd = open(ext, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(ext);
	return fd;
}

int		main(int ac, char **av)
{
	int					df;
	int					fd = open(av[1], O_RDONLY);
	size_t				i = 4;
	ssize_t				ret;
	t_champion			champ;
	unsigned char		buff[BUFF] = {0};

	if (fd == -1)
		PERROR;
	ret = read(fd, buff, BUFF);
	if (ret == -1)
		PERROR;
	if (*(unsigned int *)buff != MAGIC)
	{
		printf("BAD FORMAT FILE\n");
		exit(1);
	}
	champ.name = malloc(129);
	__builtin_memcpy(champ.name, buff + i, 128);
	champ.name[128] = 0;
	i += 132;
	champ.size = (*(buff + i + 2) << 8) | *(buff + i + 3);
	i += 4;
	champ.comment = malloc(2049);
	__builtin_memcpy(champ.comment, buff + i, 2048);
	i += 2052;
	df = add_ext(champ.name);
	dprintf(df, ".name \"%s\"\n", champ.name);
	dprintf(df, ".comment \"%s\"\n\n", champ.comment);
	while (i < ret)
	{
		int j = 0;
		while (j < 16 && op_tab[j].op_code != buff[i])
			j++;
		i += 1;
		if (j < 16)
			op_tab[j].f(buff, &i, df);
		else
			printf("shit, i didnt find the function to use for %x %lu %d!\n", buff[i - 1], ret - i, j);
	}
	return 0;
}
