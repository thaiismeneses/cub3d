/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_and_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:29:41 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/19 00:10:27 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_direction_ray(t_mlx_data *data)
{
	data->floor_ceiling.ray_dir_x0 = data->player.dir_x - data->player.plane_x;
	data->floor_ceiling.ray_dir_y0 = data->player.dir_y - data->player.plane_y;
	data->floor_ceiling.ray_dir_x1 = data->player.dir_x + data->player.plane_x;
	data->floor_ceiling.ray_dir_y1 = data->player.dir_y + data->player.plane_y;
}

void	dist_to_window(t_mlx_data *data, t_floor_ceiling *fc, int y, int flag)
{
	fc->pos_cur_y = y - HEIGHT / 2;
	fc->hight_player = 0.5 * HEIGHT;
	if (flag == 0)
	{
		fc->current_dist = fc->hight_player / fc->pos_cur_y;
		fc->floor_step_x = fc->current_dist * (fc->ray_dir_x1 - fc->ray_dir_x0) / WIDTH;;
		fc->floor_step_y = fc->current_dist * (fc->ray_dir_y1 - fc->ray_dir_y0) / HEIGHT;
		fc->floor_x = data->player.pos_x + fc->current_dist * fc->ray_dir_x0;
		fc->floor_y = data->player.pos_y + fc->current_dist * fc->ray_dir_y0;
	}
	else
	{
		fc->current_dist = fc->hight_player / (fc->pos_cur_y);
		fc->ceiling_step_x = fc->current_dist * (fc->ray_dir_x1 - fc->ray_dir_x0) / WIDTH;
		fc->ceiling_step_y = fc->current_dist * (fc->ray_dir_y1 - fc->ray_dir_y0) / HEIGHT;
		fc->ceiling_x = data->player.pos_x + fc->current_dist * fc->ray_dir_x0;
		fc->ceiling_y = data->player.pos_y + fc->current_dist * fc->ray_dir_y0;
	}
}

void	textures_ceiling_floor(t_mlx_data *data, t_floor_ceiling *fc, int flag)
{
	int	cell_x;
	int	cell_y;

	if (flag == 0)
	{
		cell_x = (int)(fc->floor_x);
		cell_y = (int)(fc->floor_y);
		fc->tex_floor_x = (int)((data->textures[5].width
			* (fc->floor_x - cell_x))) % (data->textures[5].width - 1);
		fc->tex_floor_y = (int)((data->textures[5].height
			* (fc->floor_y - cell_y))) % (data->textures[5].height - 1);
	}
	else
	{
		cell_x = (int)(fc->ceiling_x);
		cell_y = (int)(fc->ceiling_y);
		fc->tex_ceiling_x = (int)((data->textures[4].width
			* (fc->ceiling_x - cell_x))) % (data->textures[4].width - 1);
		fc->tex_ceiling_y = (int)((data->textures[4].height
			* (fc->ceiling_y - cell_y))) % (data->textures[4].height - 1);
	}
}

int	color_ceiling_floor(t_mlx_data *data, int flag)
{
	int x;
	int y;

	x = data->floor_ceiling.tex_floor_x;
	y = data->floor_ceiling.tex_floor_y;
	if (x < 0 || x >= data->textures[5].width
		|| y < 0 || y >= data->textures[5].height)
		return (0);
	if (flag == 0)
	{
		return (*((int *)(data->textures[5].addr
				+ (data->floor_ceiling.tex_floor_y
					* data->textures[5].line_length
					+ data->floor_ceiling.tex_floor_x
					* (data->textures[5].bits_per_pixel / 8)))));
	}
	else
	{
		return (*((int *)(data->textures[4].addr
				+ (data->floor_ceiling.tex_ceiling_y
					* data->textures[4].line_length
					+ data->floor_ceiling.tex_ceiling_x
					* (data->textures[4].bits_per_pixel / 8)))));
	}
}

void	draw_ceiling_floor(t_mlx_data *data)
{
	int	y;
	int	x;
	int	color_floor;
	int	color_ceiling;

	y = HEIGHT / 2;
	color_ceiling = 0;
	color_floor = 0;
	set_direction_ray(data);
	while (y < HEIGHT)
	{
		dist_to_window(data, &data->floor_ceiling, y, 0);
		dist_to_window(data, &data->floor_ceiling, y, 1);
		x = 0;
		while (x < WIDTH)
		{
			textures_ceiling_floor(data, &data->floor_ceiling, 0);
			data->floor_ceiling.floor_x += data->floor_ceiling.floor_step_x;
			data->floor_ceiling.floor_y += data->floor_ceiling.floor_step_y;
			color_floor = color_ceiling_floor(data, 0);
			my_put_pixel(&data->img, x, y, color_floor);
			textures_ceiling_floor(data, &data->floor_ceiling, 1);
			data->floor_ceiling.ceiling_x += data->floor_ceiling.ceiling_step_x;
			data->floor_ceiling.ceiling_y += data->floor_ceiling.ceiling_step_y;
			color_ceiling = color_ceiling_floor(data, 1);
			my_put_pixel(&data->img, x, HEIGHT - y - 1, color_ceiling);
			x++;
		}
		y++;
	}
}
