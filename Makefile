NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c \
	  srcs/parsing.c \
	  srcs/parse_utils.c \
	  srcs/free_file.c \
	  srcs/parsing_map_utils.c \
	  srcs/parsing_map.c \
	  srcs/raycast.c \
	  srcs/raycast_utils.c \
	  srcs/init_all.c \
	  srcs/move_player.c \
	  srcs/parse_textue.c\
	  srcs/load_textures.c \
	  srcs/draw_map.c \

OBJ = $(SRC:.c=.o)

# Header files
INCLUDES = -Iinclude -Iminilibx-linux -Ilibft

# Libraries
LIBFT = libft/libft.a
MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@make -C libft

$(MLX):
	@make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C libft clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
