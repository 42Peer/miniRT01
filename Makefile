NAME = minirt
CC = gcc
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror
SRCS = minirt.c				\
		object.c			\
		scene.c				\
		trace.c				\
		vec.c				\
		light.c

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CLIB) $(SRCS) -o $(NAME) -L./mlx -lmlx -framework OpenGL -framework AppKit -lz

%.o :%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re