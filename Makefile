# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunghye <seunghye@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/09 13:07:50 by seunghye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= miniRT

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address -g3
DEBUG	= -fsanitize=address -g3
MFLAGS	= -framework OpenGL -framework AppKit

MLX_DIR	= ./mlx
MLX 	= mlx

# INCLUDE = -I ./include

SRC_DIR = ./src
SRC = main.c scene.c structures.c print.c trace.c utils.c my_mlx.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(MLX_DIR) -l $(MLX) $(MFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) clean -C $(MLX_DIR);
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
