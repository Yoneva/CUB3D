CC = cc
NAME = cub3d
BONUS_NAME= cub3d_bonus

BUILD_DIR= build

SRC = $(shell find mandatory -type f -name "*.c")
OBJ = $(addprefix $(BUILD_DIR)/, $(SRC:.c=.o))  #$(SRC:.c=.o)

BONUS_SRC= $(shell find bonus -type f -name "*.c")
BONUS_OBJ= $(addprefix $(BUILD_DIR)/, $(BONUS_SRC:.c=.o))

HEADERS= $(shell find ../includes -type f -name "*.h" )

HEADER_DIR = ../includes

LIBFT_DIR= ../libs/Libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ../libs/MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a

CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -L$(shell brew --prefix)/opt/glfw/lib
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

INC = -I$(HEADER_DIR) -I$(MLX_DIR)/include -I../libs/Libft

all: $(BUILD_DIR) $(NAME)

bonus: $(BUILD_DIR) $(BONUS_NAME)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB) $(HEADERS)
	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) -lglfw $(FRAMEWORKS) $(LDFLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT) $(MLX_LIB) $(HEADERS)
	$(CC) $(BONUS_OBJ) $(LIBFT) $(MLX_LIB) -lglfw $(FRAMEWORKS) $(LDFLAGS) -o $(BONUS_NAME)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	cmake -S $(MLX_DIR) -B $(MLX_DIR)/build -DCMAKE_PREFIX_PATH="$(HOME)/.brew;/opt/homebrew"
	cmake --build $(MLX_DIR)/build -j4

clean:
	rm -rf $(BUILD_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
