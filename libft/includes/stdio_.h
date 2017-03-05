/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio_.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 15:38:31 by rbadia            #+#    #+#             */
/*   Updated: 2017/01/31 17:45:19 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDIO__H
# define STDIO__H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>
# define PRINTF_FLAGS "-+#0 "
# define MODIFIERS_LEN 8
# define TOTAL_CONV_FUNCTIONS 15
# define PF_BUFF_SIZE 1000

int				ft_printf(const char *format, ...);
int				ft_vprintf(const char *format, va_list ap);
int				ft_dprintf(const int fd, const char *format, ...);
int				ft_sprintf(char *str, const char *format, ...);
int				ft_snprintf(char *str, size_t size, const char *format, ...);
int				ft_smprintf(char **str, const char *format, ...);

typedef struct	s_convs
{
	ssize_t		(*ft)(va_list ap, void *datavoid);
	char		specifier;
	char		padding[7];
}				t_convs;

typedef struct	s_pfinfo
{
	int			fd;
	va_list		ap;
	int			flag_padleft;
	int			flag_addplus;
	int			flag_sharp;
	int			flag_pad0;
	int			flag_addspace;
	int			min_width;
	int			precision;
	char		modifiers[MODIFIERS_LEN][3];
	char		length_modifier;
	t_convs		conv_fts[TOTAL_CONV_FUNCTIONS];
	int			printed_char;
	char		char_to_print;
	char		buffer[PF_BUFF_SIZE + 1];
	ssize_t		buff_idx;
	char		*full_buff;
	int			bufferise_whole_printf;
	int			buff_sprintf;
	ssize_t		buff_limit;
	char		error;
}				t_pf;

/*
** printf related functions
*/

int				get_bitwise_flag(char flag, int index);
int				set_bitwise_flag(char *flag, int index);
int				set_bitwise_flag_zero(char *flag, int index);
const char		*set_flags(const char *format, t_pf *data);
void			clear_flags(t_pf *data);

const char		*set_min_width(const char *format, t_pf *data);
const char		*set_precision(const char *format, t_pf *data);
const char		*set_size(const char *format, t_pf *data);
const char		*set_conv_type(const char *format, va_list ap, t_pf *data);

ssize_t			printf_int(va_list ap, void *datavoid);
ssize_t			printf_uint(va_list ap, void *datavoid);
ssize_t			put_uint(uintmax_t nbr, t_pf *data, char *b, char *p);
ssize_t			printf_str(va_list ap, void *datavoid);
ssize_t			printf_char(va_list ap, void *datavoid);
ssize_t			printf_octal(va_list ap, void *datavoid);
ssize_t			printf_long_octal(va_list ap, void *datavoid);
ssize_t			printf_percent(va_list ap, void *datavoid);
ssize_t			printf_hex(va_list ap, void *datavoid);
ssize_t			printf_big_hex(va_list ap, void *datavoid);
ssize_t			printf_ptr(va_list ap, void *datavoid);
ssize_t			printf_longint(va_list ap, void *datavoid);
ssize_t			printf_longuint(va_list ap, void *datavoid);
ssize_t			printf_wchar(va_list ap, void *datavoid);
ssize_t			printf_wstr(va_list ap, void *datavoid);
ssize_t			printf_error(va_list ap, void *datavoid);
int				put_uint_prefix(uintmax_t nb, char *b, t_pf *data, char *p);
unsigned int	nbrlen_withpadding(uintmax_t nb, char *b, char *p, t_pf *data);
void			putnbr_base_with_precision(uintmax_t nbr, char *b, t_pf *data);

int				ft_vprintf_withinfo(const char *format, va_list ap,
	t_pf *data);
void			putpadding(t_pf *data, int nb_len_with_padding, int width,
	char padwith);
unsigned int	calculate_strlen_from_nbr(uintmax_t nbr, char *b, char *p,
	t_pf *data);
unsigned int	nbrbase_len(uintmax_t nbr, char *b);
void			prepare_info_data(t_pf *data);
void			buffwrite_c(t_pf *data, char c);
void			putwc_buf(t_pf *data, wchar_t chr);
int				puts_buf(t_pf *data, const char *s);
void			putws_buf(t_pf *data, wchar_t const *str);
void			putwsn_buf(t_pf *data, wchar_t const *str, size_t size);
int				puts_n_buf(t_pf *data, const char *s, size_t n);

/*
** printf related defines
*/
# define IS_HH_MODIFIER get_bitwise_flag(data->length_modifier, 0)
# define IS_H_MODIFIER get_bitwise_flag(data->length_modifier, 1)
# define IS_LL_MODIFIER get_bitwise_flag(data->length_modifier, 2)
# define IS_L_MODIFIER get_bitwise_flag(data->length_modifier, 3)
# define IS_J_MODIFIER get_bitwise_flag(data->length_modifier, 4)
# define IS_T_MODIFIER get_bitwise_flag(data->length_modifier, 5)
# define IS_Z_MODIFIER get_bitwise_flag(data->length_modifier, 6)
# define IS_BIG_L_MODIFIER get_bitwise_flag(data->length_modifier, 7)

#endif
