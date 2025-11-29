CC = cc
NAME = cub3d

SRC = main.c \
	parsing/parsing.c parsing/parse_map.c parsing/parse_texture.c \
	parsing/Utils/ft_realloc.c parsing/Utils/count_word.c parsing/Utils/rectangle_map.c parsing/Utils/parse_texture_utils.c \
	raycasting/raycasting.c raycasting/keys_event.c raycasting/cast_ray.c raycasting/draw_frame.c raycasting/intersections.c raycasting/player_pos.c \
	raycasting/utils.c raycasting/mini_map.c  texturing/textures.c  texturing/helper.c \
	../libs/get_next_line/get_next_line.c ../libs/get_next_line/get_next_line_utils.c
OBJ = $(SRC:.c=.o)

HEADER_DIR = ../includes

LIBFT = ../libs/Libft/libft.a
MLX_DIR = ../libs/MLX42
MLX_INC = $(MLX_DIR)/include
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -L$(shell brew --prefix)/opt/glfw/lib
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

INC = -I$(HEADER_DIR) -I$(MLX_INC) -I../libs/Libft -I../libs/get_next_line

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) -lglfw $(FRAMEWORKS) $(LDFLAGS) -o $(NAME)

%.o: %.c ../includes/raycasting.h ../includes/parsing.h
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ../libs/Libft

$(MLX_LIB):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build -DCMAKE_PREFIX_PATH="$(HOME)/.brew;/opt/homebrew"
	cmake --build $(MLX_DIR)/build -j4

clean:
	rm -f $(OBJ)
	$(MAKE) -C ../libs/Libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ../libs/Libft fclean

re: fclean all

.PHONY: all clean fclean re
