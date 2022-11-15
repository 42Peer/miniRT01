# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seunghye <seunghye@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/26 18:07:13 by mher              #+#    #+#              #
#    Updated: 2022/11/14 15:15:07 by seunghye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= libvec.a

AR		= ar
ARFLAGS	= -crs
CC		= cc
CFLAGS	= -Wall -Wextra -Werror

INCLUDE = -I./include

SRC = \
	./color3.c\
	./point3.c\
	./vcross.c\
	./vdivide_k.c\
	./vdot.c\
	./vec3.c\
	./vector.h\
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
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	@ar crsu $(NAME) $@
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
