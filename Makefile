CC = cc

NAME = miniRT

# CFLAGS = 
CFLAGS = -g -fsanitize=address
# CFLAGS = -Wall -Werror -Wextra -fsanitize=thread

SRCS = mlx_main.c canvas.c ray.c scene.c vec3_utils.c hit_sphere.c \
		object_create.c normal.c hit.c object_utils.c phong_lighting.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I. $(OBJS) -o $(NAME) -Lmlx -lmlx

%.o : %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

all : $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
re:
	make fclean
	make all

.PHONY: all clean fclean re