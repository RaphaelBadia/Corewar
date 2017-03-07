/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 18:08:24 by jye               #+#    #+#             */
/*   Updated: 2017/03/07 22:55:47 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <ncurses.h>
#include "vm.h"
#include "graphic.h"

#define HEADER_SIZE (sizeof(t_header))
#define DMP_FLAG "-dump"
#define IDP_FLAG "-n"
#define VIS_FLAG "--visual"
#define AFF_FLAG "-a"
#define STOP_FLAG "-s"

/************************************************************************************/
/************************************************************************************/
/************************* SET CHAMPION DATA ****************************************/
/************************************************************************************/
/************************************************************************************/

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
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/***************************SET MAP**************************************************/
void	set_map(t_vm *vm)
{
	unsigned int	i;
	unsigned int	offset;

	offset = 0;
	i = 0;
	while (i < vm->nb_player)
	{
		memcpy(vm->map + offset, vm->champ[i].byte_code, vm->champ[i].size);
		//  refresh la map avec la couleur du champion, à OFFSET
		refresh_map(vm, offset, vm->champ[i].size, vm->champ[i].id_player);
		offset += MEM_SIZE / vm->nb_player;
		++i;
	}
	refresh();
	// sleep(1);
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
	i = -1;
	printf("         ");
	while (++i < 64)
		printf("%.2d ", i);
	printf("\n");
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

/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

t_process	*init_process__(unsigned int r1, unsigned int pc)
{
	t_process	*new_p;

	if ((new_p = malloc(sizeof(t_process))) == NULL)
		return (NULL);
	memset(new_p, 0, sizeof(t_process));
	new_p->r[0] = r1;
	new_p->pc = pc;
	new_p->id_player = r1;
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

void	reset_live(t_vm *vm)
{
	unsigned int	i;

	i = 0;
	while (i < vm->nb_player)
	{
		vm->champ[i].live = 0;
		++i;
	}
}

void	checks(t_vm *vm)
{
	if (vm->cycle == 0)
		return ;
	if (vm->live > 20)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	else if (vm->checks == 9)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->checks = 0;
	}
	else
		vm->checks += 1;
	reset_live(vm);
	vm->live = 0;
}

/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/

unsigned int	check_octal(t_vm *vm, t_process *process)
{
	int				i;
	unsigned int	offset;
	unsigned char	byte_code;
	unsigned char	octal;
	unsigned char	octal_code;

	byte_code = process->op_code;
	i = 0;
	offset = 6;
	if (!g_op_tab[byte_code].octal)
		return (0);
	octal_code = vm->map[PTR(process->pc + 1)];
	while (i < g_op_tab[byte_code].argc)
	{
		octal = (octal_code >> offset) & 3;
		if (((g_op_tab[byte_code].argv[i] & T_DIR) && octal == DIR_CODE) ||
			((g_op_tab[byte_code].argv[i] & T_REG) && octal == REG_CODE) ||
			((g_op_tab[byte_code].argv[i] & T_IND) && octal == IND_CODE))
			++i;
		else
			return (nskip(byte_code, octal_code));
		offset -= 2;
	}
	if (test_reg(vm, byte_code, octal_code, process->pc))
		return (nskip(byte_code, octal_code));
	else
		return (0);
}

void	exec_opt(t_vm *vm, t_process *process)
{
	static void		(*f[])() = {NULL, &live, &ld, &st, &add, &sub, &and,
								&or, &xor, &zjmp, &ldi, &sti, &frk, &lld,
								&lldi, &lfork};
	unsigned char	byte_code;
	unsigned int	octal_skip;

	unlight(vm, process->pc, 1);
	if (!(octal_skip = check_octal(vm, process)))
	{
		f[process->op_code](vm, process);
	}
	else
	{
		process->pc += octal_skip;
	}
	process->op_code = 0;
	process->exec_cycle = 0;
	byte_code = vm->map[PTR(process->pc)];
	if (byte_code > 0 && byte_code <= 16)
	{
		process->op_code = byte_code;
		process->exec_cycle = g_op_tab[byte_code].cycles + vm->cycle;
		highlight(vm, process->pc, 1, -1);
	}
	else
	{
		unlight(vm, process->pc, 1);
		if (++process->pc >= MEM_SIZE)
			process->pc = process->pc % MEM_SIZE;
		highlight(vm, process->pc, 1, -1);
	}
}

void	check_opt(t_vm *vm)
{
	unsigned char	byte_code;
	t_process		*cp;
	t_lst			*process;

	process = vm->process;
	while (process)
	{
		cp = process->data;
		byte_code = vm->map[PTR(cp->pc)];
		if (!cp->op_code && byte_code > 0 && byte_code <= 16)
		{
			highlight(vm, cp->pc, 1, -1);
			cp->op_code = byte_code;
			cp->exec_cycle = g_op_tab[byte_code].cycles + vm->cycle;
		}
		else if (cp->exec_cycle == vm->cycle)
		{
			exec_opt(vm, cp);
		}
		else if (!cp->op_code)
		{
			unlight(vm, cp->pc, 1);
			if (++cp->pc > MEM_SIZE)
				cp->pc = cp->pc % MEM_SIZE;
			highlight(vm, cp->pc, 1, -1);
		}
		process = process->next;
	}
}

void	purge_process(t_vm *vm, unsigned long last_check)
{
	t_process	*pro;
	t_lst		*cp;

	if (vm->cycle == 0)
		return ;
	else if (vm->cycle_to_die & 0xf0000000)
	{
		while (vm->process)
			pop_lst__(&vm->process, &free);
		return ;
	}
	cp = vm->process;
	while (cp && (pro = cp->data))
	{
		if (!pro->last_live || (pro->last_live < last_check))
		{
			unlight(vm, pro->pc, 1);
			vm->nb_process -= 1;
			pop_lst__(&cp, &free);
		}
		else
			break ;
	}
	vm->process = cp;
	while (cp)
	{
		pro = cp->data;
		if (!pro->last_live || (pro->last_live < last_check))
		{
			unlight(vm, pro->pc, 1);
			vm->nb_process -= 1;
			pop_lst__(&cp, &free);
		}
		else
			cp = cp->next;
	}
}

void	play(t_vm *vm)
{
	unsigned long	last_check;

	vm->process = init_process(vm);
	last_check = 0;
	while (vm->process)
	{
		check_opt(vm);
		vm->cycle += 1;
		if (last_check == vm->cycle - vm->cycle_to_die)
		{
			checks(vm);
			purge_process(vm, last_check);
			last_check = vm->cycle;
		}
		info_curses(vm);
		refresh();
		// usleep(1000);
	}
	getch();
	dprintf(2, "Game over cycle:%lu\n", vm->cycle);
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
	init_ncurses(&vm);
	hardcoded_shit(vm);
	set_map(&vm);
	vm.cycle_to_die = CYCLE_TO_DIE;
	play(&vm);
	// info_curses(&vm);
	endwin();
	// print_map(vm.map);
	return (0);
}
