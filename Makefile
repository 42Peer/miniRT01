# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: junkpark <junkpark@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by junkpark          #+#    #+#              #
#    Updated: 2022/11/09 11:50:09 by junkpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= miniRT

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
MFLAGS	= -framework OpenGL -framework AppKit

MLX_DIR	= ./minilibx_opengl_20191021
MLX 	= mlx

# INCLUDE = -I ./include

SRC = main.c scene.c

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
