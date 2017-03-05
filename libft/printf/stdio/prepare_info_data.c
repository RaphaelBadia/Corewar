/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_info_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:47:36 by rbadia            #+#    #+#             */
/*   Updated: 2016/12/19 16:40:17 by rbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "string_.h"
#include "stdio_.h"

static void		get_len_modifiers(char modifiers[MODIFIERS_LEN][3])
{
	bzero_(modifiers, MODIFIERS_LEN * 3);
	strcpy_(modifiers[0], "hh");
	strcpy_(modifiers[1], "h");
	strcpy_(modifiers[2], "ll");
	strcpy_(modifiers[3], "l");
	strcpy_(modifiers[4], "j");
	strcpy_(modifiers[5], "t");
	strcpy_(modifiers[6], "z");
	strcpy_(modifiers[7], "L");
}

static void		set_flags_data(t_pf *data)
{
	data->flag_padleft = 0;
	data->flag_addplus = 0;
	data->flag_sharp = 0;
	data->flag_pad0 = 0;
	data->flag_addspace = 0;
	data->length_modifier = 0;
	data->precision = 0;
	data->min_width = 0;
}

static void		set_conv_functions_1(t_pf *data)
{
	data->conv_fts[0].specifier = 'd';
	data->conv_fts[0].ft = &printf_int;
	data->conv_fts[1].specifier = 'u';
	data->conv_fts[1].ft = &printf_uint;
	data->conv_fts[2].specifier = 's';
	data->conv_fts[2].ft = &printf_str;
	data->conv_fts[3].specifier = 'c';
	data->conv_fts[3].ft = &printf_char;
	data->conv_fts[4].specifier = 'o';
	data->conv_fts[4].ft = &printf_octal;
	data->conv_fts[5].specifier = 'O';
	data->conv_fts[5].ft = &printf_long_octal;
	data->conv_fts[6].specifier = '%';
	data->conv_fts[6].ft = &printf_percent;
	data->conv_fts[7].specifier = 'x';
	data->conv_fts[7].ft = &printf_hex;
	data->conv_fts[8].specifier = 'i';
	data->conv_fts[8].ft = &printf_int;
	data->conv_fts[9].specifier = 'p';
	data->conv_fts[9].ft = &printf_ptr;
	data->conv_fts[10].specifier = 'D';
	data->conv_fts[10].ft = &printf_longint;
	data->conv_fts[11].specifier = 'X';
	data->conv_fts[11].ft = &printf_big_hex;
}

static void		set_conv_functions_2(t_pf *data)
{
	data->conv_fts[12].specifier = 'U';
	data->conv_fts[12].ft = &printf_longuint;
	data->conv_fts[13].specifier = 'C';
	data->conv_fts[13].ft = &printf_wchar;
	data->conv_fts[14].specifier = 'S';
	data->conv_fts[14].ft = &printf_wstr;
}

void			prepare_info_data(t_pf *data)
{
	set_flags_data(data);
	get_len_modifiers(data->modifiers);
	set_conv_functions_1(data);
	set_conv_functions_2(data);
	data->fd = 1;
	data->buff_idx = 0;
	data->full_buff = NULL;
	data->bufferise_whole_printf = 0;
	data->buff_sprintf = 0;
	data->buff_limit = INTMAX_MAX;
	data->error = 0;
}
