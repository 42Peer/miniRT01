# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jujeon <jujeon@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/16 15:17:20 by jujeon           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME 	= libvec.a

AR		= ar
ARFLAGS	= -crs
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

INCLUDE = -I.

SRC = \
	./color3.c\
	./point3.c\
	./vcross.c\
	./vdivide_k.c\
	./vdot.c\
	./vec3.c\
	./vlength.c\
	./vlength2.c\
	./vmin.c\
	./vminus.c\
	./vmult.c\
	./vmult_k.c\
	./vplus.c\
	./vset.c\
	./vunit.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	@ar crsu $(NAME) $@
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re