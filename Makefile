# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 14:30:18 by rhvidste          #+#    #+#              #
#    Updated: 2025/01/30 11:15:42 by rhvidste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#colors------------------------------------------------------------------------------
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
#------------------------------------------------------------------------------------
NAME	= fdf
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX 	= ./lib/MLX42
LIBFT	= ./lib/libft/libft.a

HEADERS = -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	= $(shell find $(SRC_DIR) -iname "*.c")
#OBJS	= ${SRCS:.c=.o}
OBJS 	= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))



INC		= include/
SRC_DIR = src/
OBJ_DIR = obj/

start:
		make all

all: libmlx $(NAME)

libmlx:
		@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
		make -C ./lib/libft

#%.o: %.c
#		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)
		@echo "$(GREEN)Succesfully built fdf!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $@

clean:
		#@rm -rf $(OBJS)
		@rm -rf $(OBJ_DIR)
		@rm -rf $(LIBMLX)/build
		@make clean -C ./lib/libft

fclean: clean
		@rm -rf $(NAME)
		@rm -rf $(LIBFT)
		@echo "$(CYAN)fdf executable files cleaned!$(DEF_COLOR)"
		@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"

re: clean all
		@echo "$(GREEN)Cleaned and rebuilt everything for fdf!$(DEF_COLOR)"

.PHONY: all, clean, fclean, re, libmlx
