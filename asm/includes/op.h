/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:33:37 by rbadia            #+#    #+#             */
/*   Updated: 2017/02/25 19:00:52 by rbadia           ###   ########.fr       */
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

# include <stddef.h>

typedef char		t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define T_REGB					1
# define T_DIRB					2
# define T_INDB					3

/*
** Header du programme
** Je ne sais pas ce qu'est le "magic"
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define PROG_INSTRUCTS_START	(4 + 128 + 1 + 3 + 4 + 2048 + 1 + 3)

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_label
{
	char						*label_name;
	int							index;
	int							index_op;
	int							line;
	int							column;
	struct s_label				*next;
}								t_label;

# define BUFFSIZE				42

typedef struct					s_asm
{
	t_header					header;
	int							line;
	int							column;
	t_label						*to_fill;
	t_label						*knowns;
	unsigned char				*buffer;
	unsigned int				buff_index;
	unsigned int				buff_len;
}								t_asm;

/*
** Tableau des operations
** https://docs.google.com/spreadsheets/d/
** 1xTy1fQmra797pfamd0OBy2Q11sCwJpxEUd5i_7tp2EY/edit?usp=sharing
*/

typedef struct					s_instruction
{
	char						op_buff[11];
	int							op_i;
	int							args_i;
}								t_instruction;

typedef struct					s_op
{
	char						*name;
	int							argc;
	int							argv[3];
	int							opcode;
	int							cycles;
	char						*desc;
	int							octal;
	int							label_size;
	void						(*op)(t_asm *data, char **args);
}								t_op;

extern							t_op g_ops[];

void							read_header(t_asm *data, int fd);
void							read_program(t_asm *data, int fd);
void							check_type(t_instruction *ins, int type,
		int type_argi, t_asm *data);
int								get_param(t_instruction *ins, char *param,
		t_asm *data, int dir_size);

/*
** label functions
*/

int								fill_label(char *name, t_asm *data,
		char *op_buff, int *op_i);
void							fill_label_to_fill(t_asm *data);
void							ft_addlabel(t_label **lst, char *name,
		int index, int index_op);
void							display_labels(t_label *lst);
void							display_to_fill_list(t_label *lst);
t_label							*ft_find_label_in_lst(char *name, t_label *lst);
char							*get_label(t_asm *data, char *line);
int								get_label_to_find(t_asm *data, char *line,
		char *op_buff, int *op_i);

/*
** op functions
*/

void							op_live(t_asm *data, char **args);
void							op_ld(t_asm *data, char **args);
void							op_st(t_asm *data, char **args);
void							op_add(t_asm *data, char **args);
void							op_sub(t_asm *data, char **args);
void							op_and(t_asm *data, char **args);
void							op_or(t_asm *data, char **args);
void							op_xor(t_asm *data, char **args);
void							op_zjmp(t_asm *data, char **args);
void							op_ldi(t_asm *data, char **args);
void							op_sti(t_asm *data, char **args);
void							op_fork(t_asm *data, char **args);
void							op_lld(t_asm *data, char **args);
void							op_lldi(t_asm *data, char **args);
void							op_lfork(t_asm *data, char **args);
void							op_aff(t_asm *data, char **args);
void							op_nothing(t_asm *data, char **args);

/*
** utils
*/

char							*remove_comment(char *str);
size_t							ft_strstrlen(char **str);
int								empty(char *str);
void							ft_exit_err(char *msg, t_asm *data);
int								is_one_of(char c, char *that);
int								ft_strchri(char *str, int i);
void							ft_cpy_buf(unsigned char *src, t_asm *data,
		size_t n);
int								swap_bits(int integer);
char							*ft_strndup(const char *s, size_t n);
char							**splitrim(char *str, t_asm *data);
int								ft_atoi_safe(const char *str, int *result);

#endif
