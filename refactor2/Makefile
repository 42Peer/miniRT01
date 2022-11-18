# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnam <jnam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/18 16:00:05 by jnam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 	= miniRT

CC		= cc
CFLAGS	= -g3 -fsanitize=address # -Wall -Wextra -Werror
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
		validator/validator.c

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
