# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 14:30:18 by rhvidste          #+#    #+#              #
#    Updated: 2025/02/13 11:43:06 by rhvidste         ###   ########.fr        #
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
NAME	= 	fdf
BNAME	=	fdf_bonus

CC		= 	cc
CFLAGS	= 	-Wextra -Wall -Werror -Wunreachable-code -O3 -g
LIBMLXDIR 	= 	./lib/MLX42
LIBFT	= 	./lib/libft/libft.a

HEADERS = 	-I ./include -I $(LIBMLXDIR)/include
LIBS	= 	$(LIBMLXDIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
#-----------------------------------------------------------------------------------
SRCS	=	src/fdf.c \
			src/mlx.c \
			src/utils.c \
			src/error.c \
			src/init_data.c \
			src/init_arr.c \
			src/read_map.c \
			src/parse_map.c \
			src/matrix_projection.c \
			src/matrix_transforms.c \
			src/matrix_operations.c \
			src/transform_operations.c \
			src/orthographic_projection.c \
			src/line_draw_utils.c \
			src/line_draw.c \
			src/2d_operations.c \
			src/draw_operations.c
#-----------------------------------------------------------------------------------
BSRCS	=	src_bonus/bonus_2d_operations.c \
			src_bonus/bonus_3d_operations.c \
			src_bonus/bonus_draw_operations.c \
			src_bonus/bonus_error.c \
			src_bonus/bonus_fdf.c \
			src_bonus/bonus_init_arr.c \
			src_bonus/bonus_init_data.c \
			src_bonus/bonus_keyhook_functions.c \
			src_bonus/bonus_keyhooks01.c \
			src_bonus/bonus_keyhooks02.c \
			src_bonus/bonus_line_draw.c \
			src_bonus/bonus_line_draw_utils.c \
			src_bonus/bonus_matrix_operations.c \
			src_bonus/bonus_matrix_projection.c \
			src_bonus/bonus_matrix_transforms.c \
			src_bonus/bonus_mlx.c \
			src_bonus/bonus_orthographic_projection.c \
			src_bonus/bonus_parse_map.c \
			src_bonus/bonus_perspective_projection.c \
			src_bonus/bonus_read_map.c \
			src_bonus/bonus_transform_operations.c \
			src_bonus/bonus_utils.c
#------------------------------------------------------------------------------------
OBJS 		= 	$(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))
BOBJS		=	$(patsubst $(BSRC_DIR)%.c,$(BOBJ_DIR)%.o,$(BSRCS))
#------------------------------------------------------------------------------------
INC			= 	include/
SRC_DIR 	= 	src/
OBJ_DIR 	= 	obj/
BSRC_DIR	=	src_bonus/
BOBJ_DIR	=	bonus_obj/
#------------------------------------------------------------------------------------
all: $(LIBMLXDIR) libmlx $(LIBFT) $(NAME)

libmlx:
		@cmake $(LIBMLXDIR) -B $(LIBMLXDIR)/build && make -C $(LIBMLXDIR)/build -j4

$(LIBMLXDIR):
		@git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLXDIR)
		@echo "$(CYAN)cloned MLX library$(DEF_COLOR)"

$(LIBFT):
		make -C ./lib/libft

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)
		@echo "$(GREEN)Succesfully built fdf!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
		@mkdir -p $@
#--------------------------------------------------------------------------------
clean:
		@rm -rf $(OBJ_DIR)
		@rm -rf $(BOBJ_DIR)
		@make clean -C ./lib/libft
		@make clean -C ./lib/MLX42/build

fclean: clean
		@rm -rf $(NAME)
		@rm -rf $(BNAME)
		@rm -rf $(LIBFT)
		@rm -rf $(LIBMLXDIR)
		@echo "$(CYAN)fdf executable files cleaned!$(DEF_COLOR)"
		@echo "$(CYAN)libft executable files cleaned!$(DEF_COLOR)"
		@echo "$(CYAN)mlx executable files cleaned!$(DEF_COLOR)"

re: fclean all
		@echo "$(GREEN)Cleaned and rebuilt everything for fdf!$(DEF_COLOR)"
#-------------------------------------------------------------------------------
bonus: $(BNAME)

$(BNAME): $(LIBMLXDIR) libmlx $(LIBFT) $(BOBJS)
		@$(CC) $(CFLAGS) $(BOBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(BNAME)
		@echo "$(GREEN)Succesfully built fdf_bonus!$(DEF_COLOR)"

$(BOBJ_DIR)%.o:$(BSRC_DIR)%.c
		@mkdir -p $(@D)
		@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(BOBJ_DIR):
		mkdir -p $(BOBJ_DIR)
#-------------------------------------------------------------------------------
.PHONY: all clean fclean re libmlx bonus
