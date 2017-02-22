/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 18:08:24 by jye               #+#    #+#             */
/*   Updated: 2017/02/22 22:59:21 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "vm.h"
#define HEADER_SIZE (sizeof(t_header))
#define DMP_FLAG "-dump"
#define IDP_FLAG "-n"
#define VIS_FLAG "--visual"

t_champ	*init_champ__(void)
{
	t_champ	*new;

	if ((new = malloc(sizeof(t_champ) * MAX_PLAYERS)) == NULL)
		return (NULL);
	memset(new, 0, sizeof(t_champ) * MAX_PLAYERS);
	return (new);
}

void	set_flag(t_vm *vm, t_arg *arg)
{
	while (++arg->i < arg->ac)
		if (!strcmp(arg->av[arg->i], DMP_FLAG) && (vm->flag |= dump))
		{
			vm->flag |= 1;
			if (arg->i + 1 > arg->ac)
			{
				//USAGE
				exit(2);
			}
			else
				vm->dump_cycle = atoi(arg->av[++arg->i]);
		}
		else
			return ;
}

void	set_champ_data(t_champ *champ, char *file)
{
	int				fd;
	static int		id_player = 0;
	ssize_t			ret;
	unsigned char	buff[HEADER_SIZE];

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(ERROR);
		exit(errno);
	}
	if ((ret = read(fd, buff, HEADER_SIZE)) < (long)HEADER_SIZE)
	{
		if (ret == -1)
			perror(ERROR);
		else
			printf("Incorrect header size");
		exit(errno);
	}
	if (((buff[0] << 24) | (buff[1] << 16) | ((buff[2] << 8) | (buff[3]))) != COREWAR_EXEC_MAGIC)
	{
		printf("Bad header\n");
		exit(0);
	}
	if (!champ->id_player)
		champ->id_player = --id_player;
	champ->name = malloc(129);
	champ->name[128] = 0;
	champ->size = (buff[138] << 8) | buff[139];
	memcpy(champ->name, buff + 4, 128);
	champ->comment = malloc(2049);
	champ->comment[2048] = 0;
	memcpy(champ->comment, buff + 140, 2048);
	ret = read(fd, buff, HEADER_SIZE);
	if (ret != champ->size)
	{
		printf("You can't fool me, you motherfucker\n");
		exit(1);
	}
	else if (champ->size > CHAMP_MAX_SIZE)
	{
		printf("Gladiator size too fat, please consider doing a diet\n");
		exit(1);
	}
	champ->byte_code = malloc(champ->size);
	memcpy(champ->byte_code, buff, champ->size);
	close(fd);
}

int		set_champ(t_champ *champ, t_arg *arg)
{
	int		j;

	j = 0;
	while (j < MAX_PLAYERS && arg->i < arg->ac)
	{
		if (!strcmp(arg->av[arg->i], IDP_FLAG))
		{
			if (arg->i + 1 > arg->ac)
			{
				//USAGE
				exit(2);
			}
			else
				champ[j].id_player = atoi(arg->av[++arg->i]);
		}
		else
			set_champ_data(&champ[j++], arg->av[arg->i]);
		arg->i += 1;
	}
	if (arg->i < arg->ac)
	{
		printf("Too many gladiators\n");
		exit(0);
	}
	return (j);
}

int		main(int ac, char **av)
{
	t_vm	vm;
	t_arg	arg;

	arg.ac = ac;
	arg.av = av;
	arg.i = 0;
	if (ac == 1)
	{
		exit(0);
	}
	memset(&vm, 0, sizeof(t_vm));
	set_flag(&vm, &arg);
	if ((vm.champ = init_champ__()) == NULL)
		return (1);
	vm.nb_player = set_champ(vm.champ, &arg);
	return (0);
}
