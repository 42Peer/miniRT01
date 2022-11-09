NAME 	= miniRT

CC		= gcc
CFLAGS	=  -g -fsanitize=address
MFLAGS	= -framework OpenGL -framework AppKit

MLX_DIR	= ./lib/libmlx
MLX 	= mlx

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
	$(SRC_DIR)/trace/phong_lighting.c \
	$(SRC_DIR)/trace/hit/hit.c \
	$(SRC_DIR)/trace/hit/hit_sphere.c\
	$(SRC_DIR)/trace/hit/normal.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $^ \
		-L$(MLX_DIR) -l$(MLX) $(MFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
