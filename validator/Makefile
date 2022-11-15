# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mher <mher@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/16 03:03:34 by mher             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= rt_validator

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

FT_DIR	= ./lib/Libft
FT		= ft

INCLUDE = -I./include

SRC_DIR = ./
SRC = \
	$(SRC_DIR)/main.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(FT_DIR) 
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(FT_DIR) -l$(FT)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^
	
clean:
	$(MAKE) clean -C $(FT_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(FT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
