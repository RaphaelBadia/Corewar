/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:33:37 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/09 22:14:51 by jye              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

#ifndef OP_H
# define OP_H
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** Tableau des operations
** https://docs.google.com/spreadsheets/d/
** 1xTy1fQmra797pfamd0OBy2Q11sCwJpxEUd5i_7tp2EY/edit?usp=sharing
*/

typedef struct		s_op
{
	char			*name;
	int				argc;
	int				argv[3];
	int				opcode;
	int				cycles;
	int				octal;
	int				label_size;
}					t_op;

typedef char	t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

/*
** Header du programme
** Je ne sais pas ce qu'est le "magic"
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

static const t_op		g_op_tab[17] =
{
	{0, 0, {0}, 0, 0, 0, 0},
	{"live", 1, {T_DIR},
		1, 10, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG},
		2, 5, 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG},
		3, 5, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG},
		4, 10, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG},
		5, 10, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 0},
	{"zjmp", 1, {T_DIR},
		9, 20, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		10, 25, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		11, 25, 1, 1},
	{"fork", 1, {T_DIR},
		12, 800, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG},
		13, 10, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		14, 50, 1, 1},
	{"lfork", 1, {T_DIR},
		15, 1000, 0, 1},
	{"aff", 1, {T_REG},
		16, 2, 1, 0},
};

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

#endif
