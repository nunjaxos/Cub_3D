NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../libft

SRCS = parse.c parse_utils.c
OBJS = $(SRCS:.c=.o)

LIBFT = ../libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
