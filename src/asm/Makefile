# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jye <jye@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/12 18:54:30 by jye               #+#    #+#              #
#    Updated: 2017/03/14 22:04:18 by rbadia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC		=	gcc
DEBUG	=	-g3
CFLAGS	=	-Wall -Wextra
CEXTRA	=	-pedantic
LIB_FLAG =	 -L./ft_printf -lftprintf -L./libft -lft
# Directories
SRC_PATH	= src
PATH_INCLUDES	= includes
OBJ_PATH	= obj
# Source file
SRC_FILE	=	main.c					\
				read_header.c			\
				read_program.c			\
				get_param.c				\
				label.c					\
				op/add.c				\
				op/aff.c				\
				op/and.c				\
				op/fork.c				\
				op/ld.c					\
				op/ldi.c				\
				op/lfork.c				\
				op/live.c				\
				op/lld.c				\
				op/lldi.c				\
				op/nothing.c			\
				op/or.c					\
				op/st.c					\
				op/sti.c				\
				op/sub.c				\
				op/xor.c				\
				op/zjmp.c				\
				utils/empty.c			\
				utils/ft_exit_err.c		\
				utils/is_one_of.c		\
				utils/strchri.c			\
				utils/cpy_buf.c			\
				utils/swap_bits.c		\
				utils/ft_strndup.c		\
				utils/splitrim.c		\
				utils/ft_strstrlen.c	\
				utils/ft_atoi_safe.c	\
				utils/label.c			\
				utils/remove_comment.c	\
				utils/ft_arrfree.c		\
				utils/free_lst.c		\
# Object file
OBJ_FILE	=	$(addprefix $(OBJ_PATH)/,	\
				$(addsuffix .o,				\
				$(basename $(SRC_FILE))))
# Binary name
NAME		=	asm
# Rule

all		: pretty $(NAME)

.PHONY	: clean fclean re all

clean	:
	@make -C ft_printf fclean
	@make -C libft fclean
	@rm -rf $(OBJ_PATH)

fclean	:	clean
	@rm -rf $(NAME)

re		:	fclean all

$(NAME)	: $(OBJ_FILE) lib
	@$(CC) $(OBJ_FILE) -I$(PATH_INCLUDES) $(LIB_FLAG) -o $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p $(OBJ_PATH)/utils
	@mkdir -p $(OBJ_PATH)/op
	@$(CC) $(CFLAGS) $(DEBUG) $(EXTRA) -I$(PATH_INCLUDES) -c -o $@ $<

lib		:
	@make -C ft_printf
	@make -C libft

pretty :
	@echo "                                                                                             "
	@echo "               AAA                       SSSSSSSSSSSSSSS      MMMMMMMM               MMMMMMMM"
	@echo "              A:::A                    SS:::::::::::::::S     M:::::::M             M:::::::M"
	@echo "             A:::::A                  S:::::SSSSSS::::::S     M::::::::M           M::::::::M"
	@echo "            A:::::::A                 S:::::S     SSSSSSS     M:::::::::M         M:::::::::M"
	@echo "           A:::::::::A                S:::::S                 M::::::::::M       M::::::::::M"
	@echo "          A:::::A:::::A               S:::::S                 M:::::::::::M     M:::::::::::M"
	@echo "         A:::::A A:::::A               S::::SSSS              M:::::::M::::M   M::::M:::::::M"
	@echo "        A:::::A   A:::::A               SS::::::SSSSS         M::::::M M::::M M::::M M::::::M"
	@echo "       A:::::A     A:::::A                SSS::::::::SS       M::::::M  M::::M::::M  M::::::M"
	@echo "      A:::::AAAAAAAAA:::::A                  SSSSSS::::S      M::::::M   M:::::::M   M::::::M"
	@echo "     A:::::::::::::::::::::A                      S:::::S     M::::::M    M:::::M    M::::::M"
	@echo "    A:::::AAAAAAAAAAAAA:::::A                     S:::::S     M::::::M     MMMMM     M::::::M"
	@echo "   A:::::A             A:::::A        SSSSSSS     S:::::S     M::::::M               M::::::M"
	@echo "  A:::::A               A:::::A       S::::::SSSSSS:::::S     M::::::M               M::::::M"
	@echo " A:::::A                 A:::::A      S:::::::::::::::SS      M::::::M               M::::::M"
	@echo "AAAAAAA                   AAAAAAA      SSSSSSSSSSSSSSS        MMMMMMMM               MMMMMMMM"
	@echo "                                                                                             "
