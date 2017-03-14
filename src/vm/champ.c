/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jye <jye@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 20:58:33 by jye               #+#    #+#             */
/*   Updated: 2017/03/09 22:26:41 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//
#include <string.h>

static void	set_data__(t_champ *champ, unsigned char *buff)
{
	if ((champ->name = malloc(PROG_NAME_LENGTH + 1)) == NULL)
		p_error();
	champ->name[PROG_NAME_LENGTH] = 0;
	memcpy(champ->name, buff + sizeof(int), PROG_NAME_LENGTH);
	champ->size = ((buff[136] << 24) |
					(buff[137] << 16) |
					(buff[138] << 8) |
					buff[139]);
	if ((champ->comment = malloc(COMMENT_LENGTH + 1)) == NULL)
		p_error();
	champ->comment[COMMENT_LENGTH] = 0;
	memcpy(champ->comment, buff + 140, COMMENT_LENGTH);
}

static void	set_data(t_champ *champ, char *file_name)
{
	int				fd;
	static int		id_player = 0;
	long			ret;
	unsigned char	buff[HEADER_SIZE];

	if ((fd = open(file_name, O_RDONLY)) == -1)
		p_error();
	if ((ret = read(fd, buff, HEADER_SIZE)) == -1)
		p_error();
	else if (ret < (long)HEADER_SIZE)
		vm_error("Incorrect header size.\n");
	if (((buff[0] << 24) | (buff[1] << 16) | ((buff[2] << 8) | (buff[3])))
		!= COREWAR_EXEC_MAGIC)
		vm_error("Incorrect file format.\n");
	if (!champ->id_player)
		champ->id_player = --id_player;
	set_data__(champ, buff);
	ret = read(fd, buff, HEADER_SIZE);
	if (ret != champ->size)
		vm_error("Sorry but ain't smart enugh to fool me.\n");
	else if (champ->size > CHAMP_MAX_SIZE)
		vm_error("Gladiator size too fat, please consider doing a diet.\n");
	champ->byte_code = malloc(champ->size);
	memcpy(champ->byte_code, buff, champ->size);
	close(fd);
}

int			set_champ(t_champ *champ, t_arg *arg)
{
	int		j;

	j = 0;
	while (j < MAX_PLAYERS && arg->i < arg->ac)
	{
		if (!strcmp(arg->av[arg->i], IDP_FLAG))
		{
			if (arg->i + 1 > arg->ac)
				usage(arg->av[0]);
			else
				champ[j].id_player = atoi(arg->av[++arg->i]);
		}
		else
			set_data(&champ[j++], arg->av[arg->i]);
		arg->i += 1;
	}
	if (arg->i < arg->ac)
		vm_error("Too many gladiators\n");
	return (j);
}

t_champ		*init_champ__(void)
{
	t_champ	*new;

	if ((new = malloc(sizeof(t_champ) * MAX_PLAYERS)) == NULL)
		return (NULL);
	memset(new, 0, sizeof(t_champ) * MAX_PLAYERS);
	return (new);
}
