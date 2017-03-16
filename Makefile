#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jye <jye@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/12 18:54:30 by jye               #+#    #+#              #
#    Updated: 2017/02/18 18:30:08 by jye              ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# Compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
LIB_FLAG =	 -Lft_printf -lftprintf -Llibft -lft
# Directories
SRC_PATH	= src
INC_PATH	= includes
OBJ_PATH	= obj
# Source file
SRC_FILE	=	args.c		\
			 	args1.c		\
				f_atoi.c	\
				get_line.c	\
				get_name.c	\
				link.c		\
				main.c		\
				room.c		\
				utils.c		\
				etc.c		\
				link_it.c	\
				del.c		\
				trace.c		\
				move.c
# Object file
OBJ_FILE	=	$(addprefix $(OBJ_PATH)/,	\
				$(addsuffix .o,				\
				$(basename $(SRC_FILE))))	
# Binary name
NAME		=	lem-in
# Rule

all		: pretty $(NAME)
	@printf "\r\033[2K\033[0mOK\n"

.PHONY	:	clean fclean re all

clean	:
	@make -C ft_printf fclean
	@make -C libft fclean
	@rm -rf $(OBJ_PATH)

fclean	:	clean
	@rm -rf $(NAME)

re		:	fclean all

$(NAME)	: $(OBJ_FILE) lib
	@$(CC) $(OBJ_FILE) -I$(INC_PATH) $(LIB_FLAG) -o $@

$(OBJ_PATH)/%.o		: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(DEBUG) $(EXTRA) -I$(INC_PATH) -c -o $@ $<
	@printf "\033[2K"
	@printf "\033[36mGenerating %s file\r\033[0m" $@

lib		:
	@make -C ft_printf
	@make -C libft

pretty :
	@echo "                    ___           ___                                ___     "
	@echo "                   /\__\         /\  \                              /\  \    "
	@echo "                  /:/ _/_       |::\  \                ___          \:\  \   "
	@echo "                 /:/ /\__\      |:|:\  \              /\__\          \:\  \  "
	@echo "  ___     ___   /:/ /:/ _/_   __|:|\:\  \            /:/__/      _____\:\  \ "
	@echo " /\  \   /\__\ /:/_/:/ /\__\ /::::|_\:\__\          /::\  \     /::::::::\__\ "
	@echo " \:\  \ /:/  / \:\/:/ /:/  / \:\~~\  \/__/          \/\:\  \__  \:\~~\~~\/__/"
	@echo "  \:\  /:/  /   \::/_/:/  /   \:\  \                 ~~\:\/\__\  \:\  \      "
	@echo "   \:\/:/  /     \:\/:/  /     \:\  \                   \::/  /   \:\  \     "
	@echo "    \::/  /       \::/  /       \:\__\                  /:/  /     \:\__\    "
	@echo "     \/__/         \/__/         \/__/                  \/__/       \/__/    "
