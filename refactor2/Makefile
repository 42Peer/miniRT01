# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunghye <seunghye@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/14 15:14:52 by seunghye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME 	= miniRT

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
MFLAGS	= -framework OpenGL -framework AppKit

MLX_DIR	= ./lib/libmlx
MLX 	= mlx

FT_DIR	= ./lib/libft
FT		= ft

VEC_DIR	= ./lib/vec3
VEC		= vec

INCLUDE = -I./include

SRC_DIR = ./src

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils/vec3_utils.c \
	$(SRC_DIR)/utils/object_utils.c \
	$(SRC_DIR)/print/print.c \
	$(SRC_DIR)/scene/canvas.c \
	$(SRC_DIR)/scene/scene.c \
	$(SRC_DIR)/scene/object_create.c\
	$(SRC_DIR)/trace/ray.c \
	$(SRC_DIR)/trace/phong_lighting.c\
	$(SRC_DIR)/trace/hit/hit_sphere.c\
	$(SRC_DIR)/trace/hit/hit_plane.c\
	$(SRC_DIR)/trace/hit/normal.c\
	$(SRC_DIR)/trace/hit/hit.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(MLX_DIR) -l$(MLX) $(MFLAGS) \
		-L$(FT_DIR) -l$(FT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^
	
clean:
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
