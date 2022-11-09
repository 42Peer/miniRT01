# all:
# 	make all -C mlx/
# 	gcc -L./mlx -lmlx -framework OpenGL -framework AppKit main.c
# 	./a.out

NAME		= miniRT
# LIBFT		= libft
# LIBFT_LIB	= libft.a
INC_DIR		= include
SRCS		= print.c \
			vec3_utils.c \
			canvas.c \
			scene.c \
			object_create.c \
			hit_sphere.c \
			ray.c \
			main.c \
			normal.c \
			hit.c \
			object_utils.c \
			phong_lighting.c \


OBJS		= $(SRCS:%.c=%.o)

LIBC		= ar rc
FLAGS		= -Wall -Wextra -Werror

all			:	$(NAME)
$(NAME)		:	$(OBJS)
		make all -C mlx/
		cc -o $(NAME) $(OBJS) -L./mlx -lmlx -framework OpenGL -framework AppKit
# $(NAME)		:	$(OBJS)
# 		make all -C $(LIBFT)/
# 		make all -C mlx/
# 		cc -o $(NAME) $(OBJS) -Llibft -lft -L./mlx -lmlx -framework OpenGL -framework AppKit
%.o			:	%.c
		cc $(FLAGS) -c $^ -I./ -o $@

clean		:
		rm -f $(OBJS)

fclean		:	clean
		rm -f $(NAME)
		rm -f $(NAME).ppm

# clean		:
# 		rm -f $(OBJS)
# 		make clean -C $(LIBFT)
# 		make clean -C mlx

# fclean		:	clean
# 		rm -f $(NAME)
# 		rm -f ./libft/libft.a
# 		rm -f ./mlx/libmlx.a