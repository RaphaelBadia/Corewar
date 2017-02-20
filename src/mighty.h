/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mighty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/02/20 21:07:59 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MIGHTY_H__
# define __MIGHTY_H__
# include <string.h>
# define BUFF 4096
# define MAGIC 0xf383ea00
# define EXT ".dmp"
# define REG_CODE 1 //->0b01
# define DIR_CODE 2 //->0b10
# define IND_CODE 3 //->0b11
# define PERROR									\
	do											\
	{											\
		perror("can't handle ur shit sorry");	\
		exit(1);								\
	}while(0)

typedef struct	s_champion
{
	char 			*name;
	char 			*comment;
	char 			*code;
	unsigned int	size;
}				t_champion;

typedef struct	s_op
{
	char	*op_name;
	int		param;
	int		op_code;
	int		octal;
	int		label;
	void	(*f)();
}				t_op;
/*
** LABEL = 1 -> 2
** LABEL = 0 -> 4
*/
void	live(unsigned char *buff, size_t *i, int df);
void	ld(unsigned char *buff, size_t *i, int df);
void	st(unsigned char *buff, size_t *i, int df);
void	add(unsigned char *buff, size_t *i, int df);
void	sub(unsigned char *buff, size_t *i, int df);
void	and(unsigned char *buff, size_t *i, int df);
void	or(unsigned char *buff, size_t *i, int df);
void	xor(unsigned char *buff, size_t *i, int df);
void	zjump(unsigned char *buff, size_t *i, int df);
void	ldi(unsigned char *buff, size_t *i, int df);
void	sti(unsigned char *buff, size_t *i, int df);
void	frk(unsigned char *buff, size_t *i, int df);
void	lld(unsigned char *buff, size_t *i, int df);
void	lldi(unsigned char *buff, size_t *i, int df);
void	lfork(unsigned char *buff, size_t *i, int df);
void	aff(unsigned char *buff, size_t *i, int df);

static t_op    op_tab[16] =
{
    {"live", 1,  1,   0,  0, &live},
    {"ld",   2,  2,   1,  0, &ld},
    {"st",   2,  3,   1,  0, &st},
    {"add",  3,  4,   1,  0, &add},
    {"sub",  3,  5,   1,  0, &sub},
    {"and",  3,  6,   1,  0, &and},
    {"or",   3,  7,   1,  0, &or},
    {"xor",  3,  8,   1,  0, &xor},
    {"zjmp", 1,  9,   0,  1, &zjump},
    {"ldi",  3,  10,  1,  1, &ldi},
    {"sti",  3,  11,  1,  1, &sti},
    {"fork", 1,  12,  0,  1, &frk},
    {"lld",  2,  13,  1,  0, &lld},
    {"lldi", 3,  14,  1,  1, &lldi},
    {"lfork",1,  15,  0,  1, &lfork},
    {"aff",  1,  16,  1,  0, &aff},
};
#endif
