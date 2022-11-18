# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnam <jnam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/18 17:03:14 by jnam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 	= miniRT

CC		= cc
CFLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address
MFLAGS	= -framework OpenGL -framework AppKit

MLX_DIR	= ./lib/libmlx
MLX 	= mlx

VEC_DIR	= ./lib/vec3
VEC		= vec

INCLUDE = -I./include

SRC_DIR = ./

SRC = \
		main.c	\
		parser/parser.c \
		utils/util.c \
		utils/util_object.c \
		utils/util_libft.c \
		utils/util_libft2.c \
		object/ambient.c \
		object/camera.c \
		object/cylinder.c \
		object/light.c \
		object/object.c \
		object/plane.c \
		object/sphere.c \
		wrap/wrap_open.c \
		wrap/wrap_malloc.c \
		trace/hit.c \
		trace/hit_object.c \
		trace/ray.c \
		trace/phong_lighting.c \
		mlx/ft_mlx.c \
		validator/validator.c \
		validator/valid_check.c \
		validator/valid_object.c \
		validator/valid_check_cnt.c \
		validator/valid_object_must.c \
		validator/valid_util.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(VEC_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(MLX_DIR) -l$(MLX) $(MFLAGS) \
		-L$(VEC_DIR) -l$(VEC)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^
	
clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(VEC_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(VEC_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
