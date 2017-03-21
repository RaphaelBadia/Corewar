/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:59:12 by rbadia            #+#    #+#             */
/*   Updated: 2017/03/21 22:00:57 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_H
# define REVERSE_H
# include <string.h>
# define BUFF 4096
# define MAGIC 0xf383ea00
# define EXT ".dmp"

# define REG_CODE 1
# define DIR_CODE 2
# define IND_CODE 3

typedef struct	s_disassembly
{
	char			*prog_name;
	char			*prog_comment;
	size_t			prog_size;
	int				binary_fd;
	int				output_fd;
	size_t			byte;
	ssize_t			file_size;
}				t_disassembly;

/*
** LABEL = 1 -> 2
** LABEL = 0 -> 4
*/
void			live(unsigned char *buff, size_t *i, int df);
void			ld(unsigned char *buff, size_t *i, int df);
void			st(unsigned char *buff, size_t *i, int df);
void			add(unsigned char *buff, size_t *i, int df);
void			sub(unsigned char *buff, size_t *i, int df);
void			and(unsigned char *buff, size_t *i, int df);
void			or(unsigned char *buff, size_t *i, int df);
void			xor(unsigned char *buff, size_t *i, int df);
void			zjump(unsigned char *buff, size_t *i, int df);
void			ldi(unsigned char *buff, size_t *i, int df);
void			sti(unsigned char *buff, size_t *i, int df);
void			frk(unsigned char *buff, size_t *i, int df);
void			lld(unsigned char *buff, size_t *i, int df);
void			lldi(unsigned char *buff, size_t *i, int df);
void			lfork(unsigned char *buff, size_t *i, int df);
void			aff(unsigned char *buff, size_t *i, int df);
int				get_uint32(unsigned char *buff, int i);
short			get_uint16(unsigned char *buff, int i);
int				get_code_value(int code, int is_32_bits_);
void			ft_exit(char *msg);

#endif
