# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 14:30:18 by rhvidste          #+#    #+#              #
#    Updated: 2025/01/21 11:31:39 by rhvidste         ###   ########.fr        #
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
SRCS	= $(shell find ./src -iname "*.c")
OBJS	= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
		@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBFT):
		make -C ./lib/libft

%.o: %.c
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) $(LIBFT)
		@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)
		@echo "$(GREEN)Succesfully built fdf!$(DEF_COLOR)"

clean:
		@rm -rf $(OBJS)
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
