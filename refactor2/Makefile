# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/21 13:52:27 by jujeon           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #


NAME 	= miniRT

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g3 #-fsanitize=address
MFLAGS	= -framework OpenGL -framework AppKit

MLX_DIR	= ./lib/libmlx
MLX 	= mlx

VEC_DIR	= ./lib/vec3
VEC		= vec

INCLUDE = -I./include

SRC_DIR = ./

BASE :=  main.c \
		parser/parser.c \
		utils/util.c \
		utils/util_object.c \
		utils/util_libft.c \
		utils/util_libft2.c \
		object/ambient.c \
		object/camera.c \
		object/cylinder.c \
		object/object.c \
		object/plane.c \
		object/sphere.c \
		wrap/wrap_open.c \
		wrap/wrap_malloc.c \
		trace/hit.c \
		trace/hit_object.c \
		trace/ray.c \
		mlx/ft_mlx.c \
		validator/valid_check.c \
		validator/valid_object.c \
		validator/valid_check_cnt.c \
		validator/valid_util.c \

BNS = \
	$(BASE) \
	object/light_bonus.c \
	validator/valid_object_must_bonus.c \
	validator/validator_bonus.c \
	trace/phong_lighting_bonus.c \

SRC = \
	$(BASE) \
	object/light.c \
	validator/valid_object_must.c \
	validator/validator.c \
	trace/phong_lighting.c \

OBJ = $(SRC:.c=.o)

OBJ_BNS = $(BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(MAKE) -C $(VEC_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(MLX_DIR) -l$(MLX) $(MFLAGS) \
		-L$(VEC_DIR) -l$(VEC)

bonus: $(OBJ_BNS)
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
	rm -f $(OBJ_BNS)

fclean: clean
	$(MAKE) fclean -C $(VEC_DIR)
	rm -f $(NAME)
	rm -f bonus

re: fclean all

.PHONY: all clean fclean re
