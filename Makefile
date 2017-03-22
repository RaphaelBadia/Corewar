# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jye <jye@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/12 18:54:30 by jye               #+#    #+#              #
#    Updated: 2017/03/22 22:55:35 by jye              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

LIB_FLAG =	 -Lft_printf -lftprintf -Llibft -lft
# Directories
INC_PATH	= includes
VM_SRC_PATH		= src/vm
VM_OBJ_PATH		= obj/vm
ASM_SRC_PATH	= src/asm
ASM_OBJ_PATH	= obj/asm
REV_SRC_PATH	= src/reverse
REV_OBJ_PATH	= obj/reverse
# Source file
VM_SRC_FILE	=	champ.c			\
				flag.c			\
				get_param.c		\
				init_ncurses.c	\
				main.c			\
				map.c			\
				ncurses.c		\
				opt_utils.c		\
				opt_utils2.c	\
				opts/add.c		\
				opts/aff.c		\
				opts/and.c		\
				opts/fork.c		\
				opts/ld.c		\
				opts/ldi.c		\
				opts/lfork.c	\
				opts/live.c		\
				opts/lld.c		\
				opts/lldi.c		\
				opts/or.c		\
				opts/st.c		\
				opts/sti.c		\
				opts/sub.c		\
				opts/xor.c		\
				opts/zjmp.c		\
				p_error.c		\
				process.c		\
				purge.c			\
				usage.c			\
				utils.c			\
				basic.c			\
				visual.c		\
				dump.c			\
				stop.c
ASM_SRC_FILE	=	get_param.c					\
					label.c						\
					main.c						\
					op/add.c					\
					op/aff.c					\
					op/and.c					\
					op/fork.c					\
					op/ld.c						\
					op/ldi.c					\
					op/lfork.c					\
					op/live.c					\
					op/lld.c					\
					op/lldi.c					\
					op/nothing.c				\
					op/or.c						\
					op/st.c						\
					op/sti.c					\
					op/sub.c					\
					op/xor.c					\
					op/zjmp.c					\
					read_header.c				\
					read_program.c				\
					utils/cpy_buf.c				\
					utils/empty.c				\
					utils/free_lst.c			\
					utils/ft_arrfree.c			\
					utils/ft_atoi_safe.c		\
					utils/ft_exit_err.c			\
					utils/ft_strndup.c			\
					utils/ft_strstrlen.c		\
					utils/is_one_of.c			\
					utils/label.c				\
					utils/remove_comment.c		\
					utils/splitrim.c			\
					utils/strchri.c				\
					utils/swap_bits.c
REV_SRC_FILE	=	utils.c		\
					main.c		\
					opts1.c		\
					opts2.c		\
					opts3.c
# Object file
VM_OBJ_FILE	=	$(addprefix $(VM_OBJ_PATH)/,	\
				$(addsuffix .o,				\
				$(basename $(VM_SRC_FILE))))
ASM_OBJ_FILE	=	$(addprefix $(ASM_OBJ_PATH)/,	\
				$(addsuffix .o,				\
				$(basename $(ASM_SRC_FILE))))
REV_OBJ_FILE	=	$(addprefix $(REV_OBJ_PATH)/,	\
				$(addsuffix .o,				\
				$(basename $(REV_SRC_FILE))))
# Binary name
VM_NAME		=	corewar
ASM_NAME	=	asm
REV_NAME	=	disassembly
# Rule

all		: pretty $(VM_NAME) $(ASM_NAME) $(REV_NAME)
	@printf "\r\033[2K\033[0mOK\n"

.PHONY	:	clean fclean re all

clean	:
	@make -C ft_printf fclean
	@make -C libft fclean
	@rm -rf $(VM_OBJ_PATH)
	@rm -rf $(ASM_OBJ_PATH)
	@rm -rf $(REV_OBJ_PATH)

fclean	:	clean
	@rm -rf $(VM_NAME)
	@rm -rf $(ASM_NAME)
	@rm -rf $(REV_NAME)

re		:	fclean all

$(VM_NAME)	: $(VM_OBJ_FILE) lib
	@$(CC) $(VM_OBJ_FILE) -I$(INC_PATH) $(LIB_FLAG) -o $@ -lncurses
$(ASM_NAME)	: $(ASM_OBJ_FILE) lib
	@$(CC) $(ASM_OBJ_FILE) -I$(INC_PATH) $(LIB_FLAG) -o $@ -lncurses
$(REV_NAME)	: $(REV_OBJ_FILE) lib
	@$(CC) $(REV_OBJ_FILE) -I$(INC_PATH) $(LIB_FLAG) -o $@ -lncurses

$(VM_OBJ_PATH)/%.o		: $(VM_SRC_PATH)/%.c
	@mkdir -p $(VM_OBJ_PATH)
	@mkdir -p $(VM_OBJ_PATH)/opts
	@$(CC) $(CFLAGS) $(DEBUG) $(EXTRA) -I$(INC_PATH) -c -o $@ $<
	@printf "\033[2K"
	@printf "\033[33;5;36mGenerating %s file\r\033[0m" $@
$(ASM_OBJ_PATH)/%.o		: $(ASM_SRC_PATH)/%.c
	@mkdir -p $(ASM_OBJ_PATH)
	@mkdir -p $(ASM_OBJ_PATH)/op
	@mkdir -p $(ASM_OBJ_PATH)/utils
	@$(CC) $(CFLAGS) $(DEBUG) $(EXTRA) -I$(INC_PATH) -c -o $@ $<
	@printf "\033[2K"
	@printf "\033[33;5;256mGenerating %s file\r\033[0m" $@
$(REV_OBJ_PATH)/%.o		: $(REV_SRC_PATH)/%.c
	@mkdir -p $(REV_OBJ_PATH)
	@$(CC) $(CFLAGS) $(DEBUG) $(EXTRA) -I$(INC_PATH) -c -o $@ $<
	@printf "\033[2K"
	@printf "\033[36mGenerating %s file\r\033[0m" $@
lib		:
	@make -C ft_printf
	@make -C libft

pretty :
		@echo "   ___                                       "
		@echo "  / __\___  _ __ ___ _ ____      ____ _ _ __ "
		@echo " / /  / _ \| '__/ _ \ '__\ \ /\ / / _; | '__|"
		@echo "/ /__| (_) | | |  __/ |   \ V  V / (_| | |   "
		@echo "\____/\___/|_|  \___|_|    \_/\_/ \__,_|_|   "
