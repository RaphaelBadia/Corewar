/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 18:08:24 by jye               #+#    #+#             */
/*   Updated: 2017/02/28 21:41:04 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
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
#define AFF_FLAG "-a"
#define STOP_FLAG "-s"

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

int		reset_flag(t_vm *vm, unsigned int flag)
{
	if (flag == dump && (vm->flag |= flag))
	{
		if (vm->flag & visual)
			vm->flag ^= visual;
		if (vm->flag & stop)
			vm->flag ^= stop;
	}
	else if (flag == stop && (vm->flag |= flag))
	{
		if (vm->flag & visual)
			vm->flag ^= visual;
		if (vm->flag & dump)
			vm->flag ^= dump;
	}
	else if (flag == visual && (vm->flag |= flag))
	{
		if (vm->flag & dump)
			vm->flag ^= dump;
		if (vm->flag & stop)
			vm->flag ^= stop;
	}
	return (1);
}

void	set_flag(t_vm *vm, t_arg *arg)
{
	while (++arg->i < arg->ac)
		if (!strcmp(arg->av[arg->i], DMP_FLAG) && reset_flag(vm, dump))
		{
			if (arg->i + 1 > arg->ac)
			{
				//USAGE
				exit(2);
			}
			else
				vm->dump_cycle = atoi(arg->av[++arg->i]);
		}
		else if (!strcmp(arg->av[arg->i], VIS_FLAG))
			reset_flag(vm, visual);
		else if (!strcmp(arg->av[arg->i], AFF_FLAG))
			vm->flag |= aff_flag;
		else if (!strcmp(arg->av[arg->i], STOP_FLAG) && reset_flag(vm, stop))
		{
			if (arg->i + 1 > arg->ac)
			{
				//USAGE
				exit(2);
			}
			else
				vm->stop_cycle = atoi(arg->av[++arg->i]);
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
	vm->nb_process = vm->nb_player;
	return (process);
}

int		check_lives(t_vm *vm)
{
	unsigned int	i;

	i = 0;
	while (i < vm->nb_player)
	{
		if (vm->champ[i].live >= NBR_LIVE)
		{
			return (1);
		}
		++i;
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
	if (vm->cycle == 0)
		return ;
	if (check_lives(vm))
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		RESET_LIVE(vm);
		vm->checks = 0;
	}
	else if (vm->checks == 9)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		RESET_LIVE(vm);
		vm->checks = 0;
	}
	else
	{
		RESET_LIVE(vm);
		vm->checks += 1;
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

int		check_octal(t_vm *vm, t_process *process)
{
	int	i;
	unsigned int	offset;
	unsigned char	byte_code;
	unsigned char	octal;

	byte_code = process->op_code;
	i = 0;
	offset = 6;
	if (!g_op_tab[byte_code].octal)
		return (1);
	while (i < g_op_tab[byte_code].argc)
	{
		octal = (vm->map[PTR(process->pc + 1)] >> offset) & 3;
		if ((g_op_tab[byte_code].argv[i] & T_DIR) && octal == DIR_CODE)
			++i;
		else if ((g_op_tab[byte_code].argv[i] & T_REG) && octal == REG_CODE)
			++i;
		else if ((g_op_tab[byte_code].argv[i] & T_IND) && octal == IND_CODE)
			++i;
		else
			return (0);
		offset -= 2;
	}
	return (1);
}

void	exec_opt(t_vm *vm, t_process *process, t_lst *lst_pro)
{
	static void		(*f[])() = {NULL, &live, &ld, &st, &add, &sub, &and,
								&or, &xor, &zjmp, &ldi, &sti, &frk, &lld,
								&lldi, &lfork, &aff};
	unsigned char	byte_code;

	if (check_octal(vm, process))
	{
		if (process->op_code == 12 || process->op_code == 15)
			f[process->op_code](vm, process, lst_pro);
		else
			f[process->op_code](vm, process);
	}
	else
		process->pc += 1;
	process->op_code = 0;
	process->exec_cycle = 0;
	byte_code = vm->map[PTR(process->pc)];
	if (byte_code > 0 && byte_code < 17)
	{
		process->exec_cycle = g_op_tab[byte_code].cycles + vm->cycle;
		process->op_code = g_op_tab[byte_code].opcode;
	}
}

void	check_opt(t_vm *vm, t_lst *process)
{
	unsigned char	byte_code;
	t_process		*cp;

	while (process)
	{
		cp = process->data;
		byte_code = vm->map[PTR(cp->pc)];
		if (!cp->op_code && byte_code > 0 && byte_code < 17)
		{
			cp->exec_cycle = g_op_tab[byte_code].cycles + vm->cycle; // cycle to exec opt;
			cp->op_code = byte_code;
		}
		else if (cp->exec_cycle == vm->cycle)
		{
			exec_opt(vm, cp, process);
		}
		else if (!cp->op_code)
		{
			if (++cp->pc > MEM_SIZE)
				cp->pc = 0;
		}
		process = process->next;
	}
}

void	purge_process(t_vm *vm, t_lst **process)
{
	t_process	*pro;
	t_lst		*cp;

	if (vm->cycle == 0)
		return ;
	cp = *process;
	while (cp && (pro = cp->data))
	{
		if (!pro->last_live || (pro->last_live < vm->cycle - vm->cycle_to_die))
		{
			vm->nb_process -= 1;
			pop_lst__(&cp, &free);
		}
		else
			break ;
	}
	*process = cp;
	while (cp)
	{
		pro = cp->data;
		if (!pro->last_live || (pro->last_live < vm->cycle - vm->cycle_to_die))
		{
			vm->nb_process -= 1;
			pop_lst__(&cp, &free);
		}
		else
			cp = cp->next;
	}
}

void	print_winner(t_vm *vm)
{
	unsigned int	winner;
	unsigned int	i;

	winner = 0;
	i = 1;
	while (i < 4)
	{
		if (vm->champ[winner].last_live < vm->champ[i].last_live)
			winner = i;
		++i;
	}
	printf("ANNNNNNNNNNNNNNNNNNND THE WINNER IS %s (id %d) (\"%s\") WITH A WEIGHT OF %u BYTES!", vm->champ[winner].name, vm->champ[winner].id_player, vm->champ[winner].comment, vm->champ[winner].size);
}

void	play(t_vm *vm)
{
	t_lst			*process;
	unsigned long	last_check;

	process = init_process(vm);
	last_check = 0;
	while (process)
	{
		check_opt(vm, process);
		if (last_check == vm->cycle - vm->cycle_to_die)
		{
			last_check = vm->cycle;
			checks(vm);
			purge_process(vm, &process);
		}
		vm->cycle += 1;
	}
	print_winner(vm);
}

void	play_dump(t_vm *vm)
{
	t_lst			*process;
	unsigned long	last_check;

	process = init_process(vm);
	last_check = 0;
	while (process && vm->cycle != vm->dump_cycle)
	{
		check_opt(vm, process);
		if (last_check == vm->cycle - vm->cycle_to_die)
		{
			last_check = vm->cycle;
			checks(vm);
			purge_process(vm, &process);
		}
		vm->cycle += 1;
	}
//	print_map(vm->map);
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
	set_map(&vm);
	vm.cycle_to_die = CYCLE_TO_DIE;
	if (vm.flag & dump)
		play_dump(&vm);
	else if (vm.flag & stop)
	{}
	else
		play(&vm);
	print_map(vm.map);
	return (0);
}
