/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 18:25:32 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/03/27 18:50:41 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include "X11/X.h"
# include <X11/keysym.h>
# include <ctype.h> //apagar

/*** SPEED ***/
# define MOVE_SPEED 0.1
# define MOUSE_SPEED 0.0001

/*** ANIMATION ***/
# define NUM_JELLYFISH 3

/*** ROTATION DEGREE***/
# define ROTATE 0.1

/*** SIZE_WINDOW ***/
# define WIDTH 1920
# define HEIGHT 1080
# define PADDING 0.2

/*** MINI MAP ***/
# define MINI_MAP_SCALE 8
# define MINIMAP_OFFSET_X 20
# define MINIMAP_OFFSET_Y 20
# define WHITE 0xFFFFFF
# define BLUE 0x219EBC
# define RED 0xFF0000

/*** ERRORS ***/
# define NONE_ERROR 1
# define ARGS_ERROR -1
# define EXTENSION_ERROR -2
# define FD_ERROR -3
# define MAP_ERROR -4
# define TEXTURE_ERROR -5
# define PATH_ERROR -6
# define COLOR_ERROR -7

/*** STRUCTS ***/
typedef enum s_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	NONE,
	MAP,
	DR,
}	t_type;

typedef struct s_token
{
	char			*data;
	t_type			type;
	struct s_token	*next;
}					t_token;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		x_player;
	int		y_player;
}			t_map;

typedef struct s_player
{
	char	position;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}			t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		side;
	double	prep_wall_dist;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	double	line_height;
	double	step;
	double	tex_pos;
	int		tex_num;
	int		tex_x;
	int		is_door;
}			t__ray;

typedef struct s_floor_ceiling
{
	double	ray_dir_x0;
	double	ray_dir_y0;
	double	ray_dir_x1;
	double	ray_dir_y1;
	double	hight_player;
	double	pos_cur_y;
	double	floor_x;
	double	floor_y;
	double	floor_step_x;
	double	floor_step_y;
	int		tex_floor_x;
	int		tex_floor_y;
	double	ceiling_x;
	double	ceiling_y;
	double	ceiling_step_x;
	double	ceiling_step_y;
	int		tex_ceiling_x;
	int		tex_ceiling_y;
	double	current_dist;
	int		color_floor;
	int		color_ceiling;
}			t_floor_ceiling;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_texture;

typedef struct s_animation
{
	t_texture	jf[4];
	int			current_frame;
	int			frame_time;
	int			offset_x;
	int			multi_offset_x[NUM_JELLYFISH];
}				t_animation;

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_data
{
	int				c_color;
	int				f_color;
	void			*mlx;
	void			*win;
	t_token			*tokens;
	t_player		player;
	t__ray			ray;
	char			**map;
	char			**map_frame;
	int				**map_int;
	t_floor_ceiling	floor_ceiling;
	t_texture		textures[7];
	t_animation		animation;
	t_img			img;
	int				mouse_rotation;
}					t_mlx_data;

typedef struct s_portrat
{
	size_t	lines;
	size_t	columns;
	size_t	i;
	size_t	j;
	char	**map_portrat;
}			t_portrat;

/*** main_bonus.c ***/
void	config(t_mlx_data *data);
int		game_loop(t_mlx_data *data);
int		main(int argc, char **argv);

/*** validation_bonus.c ***/
int		check_extension(char *argv, char *ext);
int		error_messages(int error);
int		check_errors(t_mlx_data *data);

/*** map_file_bonus.c ***/
int		height(char **map);
int		width(char **map);
char	**open_fd(char *map_ext);

/*** elements_bonus.c ***/
t_type	find_type(char *map, int i);
int		type_index(t_type type, int i);
int		val_rgb(t_token *tokens);
int		val_texture(t_token *tokens);

/*** parse_bonus_bonus.c ***/
char	*get_token(char *cmd, int i, int start);
t_token	*set_token_list(t_token *data, int type, char *value);

/*** tokenization.c ***/
t_token	*process_line(char **map, char *line, t_token *data);
t_token	*tokenization(char **map, t_token *data);

/*** textures.c ***/
int		verify_order(t_token *tokens);
int		is_valid_file_path(char *path);
int		xpm_file(t_token *tokens);
void	load_texture(t_mlx_data *data);

/*** val_map_bonus.c***/
int		valid_player(t_token *tokens);
int		valid_char(t_token *tokens);
int		break_map(t_token *tokens);
int		map_exist(t_token *tokens);

/*** rgb_bonus.c ***/
void	get_rgb_color_to_hex(t_mlx_data *data);
int		is_valid_number(char **rgb);
int		rgb_textures(t_token *tokens);

/*** val_wall_bonus.c ***/
int		valid_wall(t_mlx_data *data);

/*** free_bonus.c ***/
void	free_list(t_token *token);
void	free_matrix(char **matrix);
void	free_matrix_int(int **matrix);
void	free_data_struct(t_mlx_data *data);
int		free_game(t_mlx_data *data);

/*** key_settings_bonus.c ***/
int		handle_board(int keycode, t_mlx_data *data);

/*** player_bonus.c ***/
void	init_player(t_player *player);
void	find_direction(t_mlx_data *data);
void	find_plane(t_mlx_data *data);
void	find_player(t_mlx_data *data);

/*** wall_utils ***/
char	**map_to_matrix(t_token *tokens);

/*** frame_bonus.c ***/
void	put_on_portrat(char **map, t_portrat *portrat, size_t i, size_t j);
char	**make_portrat(char **map);

/*** playable_map_bonus.c ***/
void	xy_player(char **map, t_map *map_copy);
int		playable_map(t_mlx_data *data);

/*** ray_casting_bonus.c ***/
void	set_values(t_mlx_data *data, int x);
void	set_ray_direction(t_mlx_data *data);
void	algorithm_dda(t_mlx_data *data);
void	wall_distance(t_mlx_data *data);
void	wall_height(t_mlx_data *data);

/*** create_img.c ***/
void	my_put_pixel(t_img *img, int x, int y, int color);
void	create_image(t_mlx_data *data);
void	draw_vertical_line(t_mlx_data *data, int x);
void	ray_casting(t_mlx_data *data);

/*** rendering_bonus.c ***/
void	render(t_mlx_data *data);

/*** convert_map_bonus.c ***/
void	check_position(t_mlx_data *data, int i, int j);
void	convert_map(t_mlx_data *data);

/*** mini_map_bonus.c ***/
void	draw_minimap(t_mlx_data *data);

/*** moves_bonus.c ***/
void	moviments(t_mlx_data *data, int keycode);

/*** ceiling_and_floor.c ***/
void	draw_ceiling_and_floor(t_mlx_data *data);

/*** ceiling_and_floor_bonus.c ***/
void	set_direction_ray(t_mlx_data *data);
void	dist_to_window(t_mlx_data *data, t_floor_ceiling *fc, int y, int flag);
void	textures_ceiling_floor(t_mlx_data *data, t_floor_ceiling *fc, int flag);
int		color_ceiling_floor(t_mlx_data *data, int flag);

/*** draw_ceiling_floor.c ***/
void	utils_ceiling_floor(t_mlx_data *data, int x, int y);
void	draw_ceiling_floor(t_mlx_data *data);

/*** init_structs_bonus.c ***/
void	init_img(t_img *img);
void	init_textures(t_texture *texture);
void	init_floor_ceiling(t_floor_ceiling *floor_ceiling);
void	init_ray(t__ray *ray);
void	init_data(t_mlx_data *data);

/*** init_strcucts_two_bonus.c ***/
t_map	*struct_map(char **map);
void	init_portrat(t_portrat *portrat);

/*** wall_collision_collision_bonus.c ***/
int		is_valid_position(t_mlx_data *data, double new_x, double new_y);

/*** move_with_mouse_bonus.c ***/
int		mouse(int x, int y, t_mlx_data *data);

/*** animation_bonus.c ***/
void	update_animation(t_mlx_data *data);
void	draw_scaled_pixel(t_mlx_data *data, t_point base, int scale, int color);
void	draw_jellyfish_instance(t_mlx_data *data, t_point jelly_pos,
			t_texture current, int scale);
t_point	calculate_jellyfish_position(t_mlx_data *data, int i,
			t_texture current, int scale);
void	render_animation(t_mlx_data *data);

/*** init_animation_bonus.c ***/
void	init_animation(t_animation *animation);
void	load_animation(t_mlx_data *data);

#endif
