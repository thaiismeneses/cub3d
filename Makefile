NAME = cub3d

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I./libft minilibx-linux/cub3d.h

LIBS = libft/libft.a minilibx-linux/libmlx.a -L/usr/X11/lib  -lX11 -lXext -lbsd -lm
SRCS = src/main.c\
		src/init_structs.c\
		src/validation.c\
		src/map_file.c\
		src/elements.c\
		src/extra_print.c\
		src/parse.c\
		src/val_map.c\
		src/textures.c\
		src/free.c\
		src/wall_collision.c\
		src/moves.c\
		src/key_settings.c\
		src/player.c\
		src/val_wall.c\
		src/frame.c\
		src/wall_utils.c\
		src/convert_map.c\
		src/create_img.c\
		src/ray_casting.c\
		src/mini_map.c\
		src/ceiling_and_floor.c\
		src/playable_map.c\
		src/init_structs_two.c\
		src/tokenization.c\
		src/rgb.c\

BONUS = src_bonus/main_bonus.c\
		src_bonus/init_structs_bonus.c\
		src_bonus/validation_bonus.c\
		src_bonus/map_file_bonus.c\
		src_bonus/elements_bonus.c\
		src_bonus/extra_print_bonus.c\
		src_bonus/parse_bonus.c\
		src_bonus/val_map_bonus.c\
		src_bonus/textures_bonus.c\
		src_bonus/free_bonus.c\
		src_bonus/wall_collision_bonus.c\
		src_bonus/moves_bonus.c\
		src_bonus/move_with_mouse_bonus.c\
		src_bonus/key_settings_bonus.c\
		src_bonus/player_bonus.c\
		src_bonus/val_wall_bonus.c\
		src_bonus/frame_bonus.c\
		src_bonus/wall_utils_bonus.c\
		src_bonus/convert_map_bonus.c\
		src_bonus/create_img_bonus.c\
		src_bonus/rendering.c\
		src_bonus/ray_casting_bonus.c\
		src_bonus/mini_map_bonus.c\
		src_bonus/ceiling_and_floor_bonus.c\
		src_bonus/draw_ceiling_floor.c\
		src_bonus/init_animation_bonus.c\
		src_bonus/animation_bonus.c\
		src_bonus/playable_map_bonus.c\
		src_bonus/init_structs_two_bonus.c\
		src_bonus/tokenization_bonus.c\
		src_bonus/rgb_bonus.c\


OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

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
	@$(CC) $(CFLAGS) $(SRCS) $(LIBS) -o $(NAME)

bonus: $(BONUS_OBJS)
	@make bonus -s -C libft/
	@make -s -C minilibx-linux/
	@$(CC) $(CFLAGS) $(BONUS) $(LIBS) -o $(NAME)

clean:
	@make -s clean -C libft/
	@$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	@make -s fclean -C libft/
	@make -s clean -C minilibx-linux/
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

re: fclean all

val: re
	$(VALGRIND) ./cub3d maps/default.cub

val_bonus: re bonus
	$(VALGRIND) ./cub3d maps/bonus.cub

norm:
	norminette $(SRCS) ./libft ./includes

.PHONY: all clean fclean re val bonus norm

