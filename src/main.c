/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 18:08:24 by jye               #+#    #+#             */
/*   Updated: 2017/02/24 11:14:43 by seto             ###   ########.fr       */
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

/**************************************************************************************/
/**************************************************************************************/
/*************************** SET CHAMPION DATA ****************************************/
/**************************************************************************************/
/**************************************************************************************/

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
	champ->size = (buff[136] << 24) | (buff[137] << 16) | (buff[138] << 8) | buff[139];
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
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

/*****************************SET MAP**************************************************/
void	set_map(t_vm *vm)
{
	unsigned int	i;
	unsigned int	offset;

	offset = 0;
	i = 0;
	while (i < vm->nb_player)
	{
		memcpy(vm->map + offset, vm->champ[i].byte_code, vm->champ[i].size);
		offset += MEM_SIZE / vm->nb_player;
		++i;
	}
}
/*
** print format 64 bytes per line
** aka 64 / 64
*/
void	print_map(unsigned char *map)
{
	int		t;
	short	i;
	
	t = 0;
	i = 0;
	while (t < 64)
	{
		int z = 0;
		printf("0x%.4hx : ", i);
		while (z < 64)
		{
			printf("%.2hhx", map[i++]);
			++z;
			if (z < 64)
				printf(" ");
		}
		printf("\n");
		++t;
 	}
}

/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/
/**************************************************************************************/

t_process	*init_process__(unsigned int r1, unsigned int pc)
{
	t_process	*new_p;

	if ((new_p = malloc(sizeof(t_process))) == NULL)
		return (NULL);
	memset(new_p, 0, sizeof(t_process));
	new_p->r[0] = r1;
	new_p->pc = pc;
	return (new_p);
}

t_lst	*init_process(t_vm *vm)
{
	unsigned int	i;
	unsigned int	pc;
	t_lst			*process;
	t_process		*cp;

	i = 0;
	process = NULL;
	pc = 0;
	while (i < vm->nb_player)
	{
		if ((cp = init_process__(vm->champ[i].id_player, pc)) == NULL)
			exit(1);
		push_lst__(&process, cp);
		++i;
		pc += MEM_SIZE / vm->nb_player;
	}
	return (process);
}

int		check_lives(t_vm *vm)
{
	unsigned int	i;

	i = 0;
	while (i < vm->nb_player)
	{
		if (vm->champ[i].live == NBR_LIVE)
			return (1);
	}
	return (0);
}

#define RESET_LIVE(vm)							\
	do{											\
		unsigned int	i;						\
												\
		i = 0;									\
		while (i < vm->nb_player)				\
		{										\
			vm->champ[i].live = 0;				\
			++i;								\
		}										\
	}while (0)

void	checks(t_vm *vm)
{
	if (check_lives(vm))
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		RESET_LIVE(vm);
		vm->checks = 0;
	}
	else if (vm->checks == 10)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		RESET_LIVE(vm);
		vm->checks = 0;
	}
	else
	{
		vm->checks += 1;
	}
}

void	check_opt(t_vm *vm, t_lst *process)
{
	unsigned char	byte_code;
	t_process		*cp;

	while (process)
	{
		cp = process->data;
		byte_code = vm->map[cp->pc];
		if (byte_code > 0 && byte_code < 17)
		{
			cp->exec_cycle = g_op_tab[byte_code - 1].cycles + vm->cycle; // cycle to exec opt;
			cp->op_code = g_op_tab[byte_code - 1].opcode;
		}
		else
		{
			cp->pc += 1; // if op_code was not found in the current PC
		}
		process = process->next;
	}
}

void	play(t_vm *vm)
{
	t_lst		*process;
	t_process	*cp;

	process = init_process(vm);
	/* while (process) */
	/* { */
	vm->cycle = 300;
	check_opt(vm, process);
	printf("process\n");
	printf("%u\n", ((t_process *)process->data)->exec_cycle);
	printf("%u\n", ((t_process *)process->data)->op_code);
//	live(vm, process->data);
	printf("%u\n", ((t_process *)process->data)->pc);
	printf("%u\n", ((t_process *)process->data)->last_live);
	printf("champion\n");
		/* exec_opt(vm, process); */
	/* 	if (vm->cycle % vm->cycle_to_die) */
	/* 	{ */
	/* 		checks(vm); */
	/* 		purge_process(vm->cycle, &process); */
	/* 	} */
	/* 	vm->cycle += 1; */
	/* } */
	/* check_winner */
	/* print winner */
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
		// USAGE
		exit(0);
	}
	memset(&vm, 0, sizeof(t_vm));
	set_flag(&vm, &arg);
	if ((vm.champ = init_champ__()) == NULL)
		return (1);
	vm.nb_player = set_champ(vm.champ, &arg);
	if (vm.nb_player < 4)
		vm.champ = realloc(vm.champ, sizeof(t_champ) * vm.nb_player);
	set_map(&vm);
//	print_map(vm.map);
	play(&vm);
	printf("%u\n", vm.champ[0].last_live);
	printf("%u\n", vm.champ[0].live);
	return (0);
}
