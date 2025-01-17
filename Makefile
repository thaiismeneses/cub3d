NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I./libft minilibx-linux/cub3d.h

LIBS = libft/libft.a minilibx-linux/libmlx.a -L/usr/X11/lib  -lX11 -lXext -lbsd -lm
SRCS = src/main.c\

OBJS = $(SRCS:.c=.o)

RM = rm -rf

VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s

all: $(NAME)

minilibx:
	wget https://cdn.intra.42.fr/document/document/25875/minilibx-linux.tgz
	tar -xvzf minilibx-linux.tgz
	rm minilibx-linux.tgz

$(NAME): $(OBJS)
	@make bonus -s -C libft/
	@make -s -C minilibx-linux/
	@$(CC) $(FLAGS) $(SRCS) $(LIBS) -o $(NAME)


clean:
	@make -s clean -C libft/
	@$(RM) $(OBJS)

fclean: clean
	@make -s fclean -C libft/
	@make -s clean -C minilibx-linux/
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all

val: re
	$(VALGRIND) ./$(NAME) map.cub

norm:
	norminette $(SRCS) ./libft ./includes

.PHONY: all clean fclean re val norm

