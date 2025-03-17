/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:26:13 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/17 11:05:03 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# define MOUSE_SPEED 0.001

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
	NO, //0
	SO, //1
	WE, //2
	EA, //3
	F, //4
	C, //5
	NONE, //6
	MAP, //7
}	t_type;

typedef struct s_token
{
	char	*data;
	t_type	type;
	struct s_token	*next;

}	t_token;

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
	char		position;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int	map_x;
	int	map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int	step_x;
	int	step_y;
	double	side_dist_x;
	double	side_dist_y;
	int	side;
	double	prep_wall_dist;
	int	draw_start;
	int	draw_end;
	double wall_x;
	double line_height;
	double step;
	double tex_pos;
	int	tex_num;
} t__ray;

typedef struct s_floor_ceiling
{
	double ray_dir_x0;
	double ray_dir_y0;
	double ray_dir_x1;
	double ray_dir_y1;
	double hight_player;
	int pos_cur_y;
	double floor_x;
	double floor_y;
	double floor_step_x;
	double floor_step_y;
	int tex_floor_x;
	int tex_floor_y;
	double ceiling_x;
	double ceiling_y;
	double ceiling_step_x;
	double ceiling_step_y;
	int tex_ceiling_x;
	int tex_ceiling_y;
	double current_dist;
} t_floor_ceiling;

typedef struct s_img
{
	void	*img;
	char	*addr; //endereço da memória da imagem
	int	bits_per_pixel;
	int	line_length; //Quantidade de bytes por linha
	int	endian; //Ordem dos bytes na memória
}	t_img;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int	width;
	int	height;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}	t_texture;

typedef struct s_animation
{
	t_texture jf[4];
	int current_frame;
	int frame_time;
	int offset_x;
	int multi_offset_x[NUM_JELLYFISH];

}	t_animation;

typedef struct s_point {
	int x;
	int y;
}	t_point;

typedef struct s_data
{
	int c_color;
	int f_color;
	void *mlx;
	void *win;
	t_token *tokens;
	t_player player;
	t__ray ray;
	char **map;
	char **map_frame;
	int **map_int;
	t_floor_ceiling floor_ceiling;
	t_texture textures[6];
	t_animation animation;
	t_img img;
	int mouse_rotation;
}	t_mlx_data;

/*** validation.c ***/
int	check_extension(char *argv, char *ext);
int	error_messages(int error);
int	check_errors(t_mlx_data *data);

/*** map_file ***/
char	**open_fd(char *map_ext);

/*** elements.c ***/
t_type	find_type(char *map, int i);
int	type_index(t_type type, int i);
int	verify_order(t_token *tokens);
int	val_texture(t_token *tokens);

/*** parse.c ***/
char	*get_token(char *cmd, int i, int start);
t_token	*set_token_list(t_token *data, int type, char *value);
t_token	*tokenization(char **map, t_token *data);

/*** val_map.c ***/
int	map_exist(t_token *tokens);

/*** textures.c ***/
void get_rgb_color_to_hex(t_mlx_data *data);
int	is_valid_file_path(char *path);
int	xpm_file(t_token *tokens);
void	load_texture(t_mlx_data *data);


int valid_player(t_token *tokens);
int valid_char(t_token *tokens);
int break_map(t_token *tokens);
int map_exist(t_token *tokens);

/*** extra_print.c ***/
void	print_array(char **map);
void	print_token_list(t_token *head);

/*** textures ***/
int rgb_textures(t_token *tokens);
int is_valid_file_path(char *path);
int xpm_file(t_token *tokens);

/*** valid_wall ***/
int valid_wall(t_mlx_data *data);


/*** free.c ***/
void	free_list(t_token *token);
void	free_matrix(char **matrix);
void	free_matrix_int(int **matrix);
void	free_data_struct(t_mlx_data *data);
int	free_game(t_mlx_data *data);

/*** key_settings.c ***/
int	handle_board(int keycode, t_mlx_data *data);

/*** player.c ***/
void	init_player(t_player *player);
void	find_player(t_mlx_data *data);
void	find_direction(t_mlx_data *data);
void	find_plane(t_mlx_data *data);

/*** wall_utils ***/
char **map_to_matrix(t_token *tokens);

/*** frame.c ***/
char **make_portrat(char **map);
int	playable_map(t_mlx_data *data);

/*** ray_casting.c ***/
void	set_values(t_mlx_data *data, int x);
void	wall_distance(t_mlx_data *data);
void	wall_height(t_mlx_data *data);
void	set_ray_direction(t_mlx_data *data);
void	algorithm_dda(t_mlx_data *data);

/*** create_img.c ***/
void	my_put_pixel(t_img *img, int x, int y, int color);
void	create_image(t_mlx_data *data);
void	draw_vertical_line(t_mlx_data *data, int x);
void	ray_casting(t_mlx_data *data);
void	render(t_mlx_data *data);

/*** convert_map.c ***/
void	convert_map(t_mlx_data *data);


/*** mini_map.c ***/
void draw_minimap(t_mlx_data *data);

/*** moves.c ***/
void	moviments(t_mlx_data *data, int keycode);

/*** ceiling_and_floor.c ***/
void	draw_ceiling_and_floor(t_mlx_data *data);

/*** ceiling_and_floor_bonus.c ***/
void	dist_to_window(t_mlx_data *data, t_floor_ceiling *fc, int y, int flag);
void	textures_ceiling_floor(t_mlx_data *data, t_floor_ceiling *fc, int flag);
void	draw_ceiling_floor(t_mlx_data *data);

/*** init_structs.c ***/
void	init_data(t_mlx_data *data);
void	init_ray(t__ray *ray);
void	init_floor_ceiling(t_floor_ceiling *floor_ceiling);
void	init_img(t_img *img);
void	init_textures(t_texture *texture);

/*** wall_collision.c  ***/
int	is_valid_position(t_mlx_data *data, double new_x, double new_y);

/*** move_with_mouse_bonus.c ***/
int	mouse(int x, int y, t_mlx_data *data);

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
