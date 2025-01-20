# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 14:30:18 by rhvidste          #+#    #+#              #
#    Updated: 2025/01/20 15:08:31 by rhvidste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX 	= ./lib/MLX42

HEADERS = -I ./include -I $(LIBMLX)/include
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	= $(shell find ./src -iname "*.c")
OBJS	= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
		@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
		@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
		@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
		@rm -rf $(OBJS)
		@rm -rf $(LIBMLX)/build

fclean: clean
		@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
