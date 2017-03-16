/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 16:33:37 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/16 19:25:49 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# define PROG_INSTRUCTS_START	(4 + 128 + 1 + 3 + 4 + 2048 + 1 + 3)
# define T_REGB					1
# define T_DIRB					2
# define T_INDB					3

# include <stddef.h>

typedef struct					s_label
{
	char						*label_name;
	int							index;
	int							index_op;
	int							line;
	int							column;
	int							label_size;
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
	int							actual_label_size;
	int							is_indir;
}								t_asm;

typedef struct					s_instruction
{
	char						op_buff[11];
	int							op_i;
	int							args_i;
}								t_instruction;

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
void							ft_addlabelline(t_label *label, t_asm *data);
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
char							*remove_comment_header(char *str);
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
void							ft_arrfree(char **arr);
void							free_lst(t_label *lst);

#endif
