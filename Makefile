NAME = cub3d
CC = cc 
CFLAGS = -Wall -Wextra -Werror
SRC = main.c srcs/parsing/parsing.c srcs/parsing/parse_utils.c srcs/parsing/free_file.c\
	  srcs/parsing/parsing_map_utils.c srcs/parsing/parsing_map.c
OBJ = $(SRC:.c=.o)
INCLUDE = include/cub_3d.h
LIBFT = srcs/libft/libft.a
MLX = -Lmlx -lmlx -lX11 -lXext

all: $(NAME)

$(LIBFT):
	@make -C libft

$(NAME): $(OBJ) $(INCLUDE) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ)
