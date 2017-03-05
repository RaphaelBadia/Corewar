# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbadia <rbadia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/09/12 16:54:19 by rbadia            #+#    #+#              #
#    Updated: 2017/02/03 15:15:22 by rbadia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STDIO_SRCS_NAME =	printf.c			\
					dprintf.c			\
					vprintf.c			\
					sprintf.c			\
					snprintf.c			\
					smprintf.c			\
					vprintf_process.c	\
					printf_int.c		\
					printf_uint.c		\
					printf_str.c		\
					printf_char.c		\
					printf_octal.c		\
					printf_percent.c	\
					printf_error.c		\
					printf_hex.c		\
					printf_big_hex.c	\
					printf_ptr.c		\
					printf_longint.c	\
					printf_longuint.c	\
					printf_wchar.c		\
					printf_wstr.c		\
					printf_flag_utils.c	\
					printf_set_width.c	\
					printf_set_precision.c	\
					printf_set_size_modifier.c	\
					printf_set_conv.c	\
					prepare_info_data.c	\
					calculate_strlen_from_nbr.c	\
					printf_nbrlen_withpadding.c	\
					printf_putnbrbase_precision.c	\
					printf_put_uint_prefix.c	\
					printf_putpadding.c	\
					nbrbase_len.c		\
					putc_fd.c			\
					buffwrite.c			\
					putwsn_buf.c		\
					puts_n_buf.c		\
					putws_buf.c			\
					puts_buf.c			\
					putwc_buf.c			\

STDIO_SRCS = $(addprefix stdio/, $(STDIO_SRCS_NAME))


STDLIB_SRCS_NAME =	itoa.c 	\

STDLIB_SRCS = $(addprefix stdlib/, $(STDLIB_SRCS_NAME))


STRING_SRCS_NAME =	strlen.c	\
					strchr.c	\
					strchr_i.c	\
					strnchr.c	\
					strcmp.c	\
					strncmp.c	\
					strnlen.c	\
					strcpy.c	\
					strcat.c	\
					strdup.c	\
					strnew.c	\
					memset.c	\
					bzero.c		\
					strjoin.c	\

STRING_SRCS = $(addprefix string/, $(STRING_SRCS_NAME))


CTYPE_SRCS_NAME =	isdigit.c 	\

CTYPE_SRCS = $(addprefix ctype/, $(CTYPE_SRCS_NAME))


MATH_SRCS_NAME =	max.c 	\
					abs.c	\

MATH_SRCS = $(addprefix math/, $(MATH_SRCS_NAME))


SRCS_NAME = $(STDIO_SRCS)	\
			$(STRING_SRCS)	\
			$(CTYPE_SRCS)	\
			$(STDLIB_SRCS)	\
			$(MATH_SRCS)	\

PRINTFSRCS = $(addprefix printf/, $(SRCS_NAME))

OBJSNAME = $(STDIO_SRCS_NAME)	\
			$(STDLIB_SRCS_NAME)	\
			$(STRING_SRCS_NAME)	\
			$(CTYPE_SRCS_NAME)	\
			$(MATH_SRCS_NAME)	\

PRINTFOBJS	= $(OBJSNAME:.c=.o)

NAME	= libft.a

SRCS	=	ft_atoi.c			\
			ft_atoi_safe.c		\
		  ft_bzero.c			\
		  ft_isalnum.c			\
		  ft_isalpha.c			\
		  ft_isascii.c			\
		  ft_isblank.c			\
		  ft_iscntrl.c			\
		  ft_isdigit.c			\
		  ft_isgraph.c			\
		  ft_islower.c			\
		  ft_isprint.c			\
		  ft_ispunct.c			\
		  ft_isupper.c			\
		  ft_isxdigit.c			\
		  ft_itoa.c				\
		  ft_lstadd.c			\
		  ft_lstaddend.c		\
		  ft_lstdel.c			\
		  ft_lstdelone.c		\
		  ft_lstnew.c			\
		  ft_lstnew_noalloc.c	\
		  ft_lstiter.c			\
		  ft_lstmap.c			\
		  ft_lstprint.c			\
		  ft_memalloc.c			\
		  ft_memccpy.c			\
		  ft_memchr.c			\
		  ft_memcmp.c			\
		  ft_memcpy.c			\
		  ft_memdel.c			\
		  ft_memmove.c			\
		  ft_memrchr.c			\
		  ft_memset.c			\
		  ft_putchar.c			\
		  ft_putchar_fd.c		\
		  ft_putendl.c			\
		  ft_putendl_fd.c		\
		  ft_putnbr.c			\
		  ft_putnbr_fd.c		\
		  ft_putstr.c			\
		  ft_putstr_fd.c		\
		  ft_strcat.c			\
		  ft_strchr.c			\
		  ft_strclr.c			\
		  ft_strcmp.c			\
		  ft_strcpy.c			\
		  ft_strdel.c			\
		  ft_strdup.c			\
		  ft_strdupn.c			\
		  ft_strequ.c			\
		  ft_strnequ.c			\
		  ft_striter.c			\
		  ft_striteri.c			\
		  ft_strjoin.c			\
		  ft_strlcat.c			\
		  ft_strlen.c			\
		  ft_strmap.c			\
		  ft_strmapi.c			\
		  ft_strncat.c			\
		  ft_strncmp.c			\
		  ft_strncpy.c			\
		  ft_strnequ.c			\
		  ft_strnew.c			\
		  ft_strnstr.c			\
		  ft_strrchr.c			\
		  ft_strsplit.c			\
		  ft_strstr.c			\
		  ft_strsub.c			\
		  ft_strtrim.c			\
		  ft_tolower.c			\
		  ft_toupper.c			\
		  ft_pow.c				\
		  ft_upow.c				\
		  ft_atoi_base.c		\
		  ft_atoui_base.c		\
		  ft_uitoa_base.c		\
		  ft_match.c			\
		  ft_explode.c			\
		  ft_calloc.c			\
		  ft_isempty.c			\
		  ft_realloc.c			\
		  ft_append.c			\
		  ft_isempty.c			\
		  get_next_line.c		\
		  ft_arrlen.c			\
		  ft_arrfree.c			\
		  ft_arrprint.c			\
		  ft_arrdup.c			\
		  ft_arrappend.c		\
		  ft_abs.c				\
		  ft_strerror.c			\
		  ft_implode.c			\

OBJS	= $(SRCS:.c=.o)

CFLAGS += -I./includes/ -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	gcc -c $(CFLAGS) $(SRCS) $(PRINTFSRCS)
	ar rc $(NAME) $(OBJS) $(PRINTFOBJS)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJS) $(PRINTFOBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
