# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnam <jnam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/18 13:25:06 by jnam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 	= miniRT

CC		= cc
CFLAGS	= -g3 -fsanitize=address # -Wall -Wextra -Werror
MFLAGS	= -framework OpenGL -framework AppKit

MLX_DIR	= ./lib/libmlx
MLX 	= mlx

FT_DIR	= ./lib/libft
FT		= ft

VEC_DIR	= ./lib/vec3
VEC		= vec

INCLUDE = -I./include

SRC_DIR = ./

SRC = \
		main.c	\
		parser/parser.c \
		utils/utils.c \
		object/ambient.c \
		object/camera.c \
		object/cylinder.c \
		object/light.c \
		object/object.c \
		object/object_utils.c \
		object/plane.c \
		object/sphere.c \
		wrap/wrap_open.c \
		wrap/wrap_malloc.c \
		trace/hit.c \
		trace/hit_object.c \
		trace/ray.c \
		trace/phong_lighting.c \

# $(SRC_DIR)/main.c \
# $(SRC_DIR)/object/object_utils.c \
# $(SRC_DIR)/print/print.c \
# $(SRC_DIR)/scene/canvas.c \
# $(SRC_DIR)/scene/scene.c \
# $(SRC_DIR)/scene/object_create.c\
# $(SRC_DIR)/wrap/wrap_malloc.c\
#$(SRC_DIR)/trace/ray.c \
#$(SRC_DIR)/trace/phong_lighting.c\
#$(SRC_DIR)/trace/hit/hit_sphere.c\
#$(SRC_DIR)/trace/hit/hit_plane.c\
#$(SRC_DIR)/trace/hit/normal.c\
#$(SRC_DIR)/trace/hit/hit.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(FT_DIR)
	$(MAKE) -C $(VEC_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(MLX_DIR) -l$(MLX) $(MFLAGS) \
		-L$(FT_DIR) -l$(FT) \
		-L$(VEC_DIR) -l$(VEC)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^
	
clean:
	$(MAKE) clean -C $(MLX_DIR)
	$(MAKE) clean -C $(FT_DIR)
	$(MAKE) clean -C $(VEC_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(FT_DIR)
	$(MAKE) fclean -C $(VEC_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
