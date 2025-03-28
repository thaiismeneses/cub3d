/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:21:58 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/24 10:59:44 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_values(t_mlx_data *data, int x)
{
	data->ray.camera_x = 2 * x / (double)WIDTH - 1;
	data->ray.ray_dir_x = data->player.dir_x
		+ data->player.plane_x * data->ray.camera_x;
	data->ray.ray_dir_y = data->player.dir_y
		+ data->player.plane_y * data->ray.camera_x;
	data->ray.map_x = (int)data->player.pos_x;
	data->ray.map_y = (int)data->player.pos_y;
	data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
}

void	set_ray_direction(t_mlx_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y
				+ 1.0 - data->player.pos_y) * data->ray.delta_dist_y;
	}
}

void	algorithm_dda(t_mlx_data *data)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map[data->ray.map_y][data->ray.map_x] == '1')
			hit = 1;
	}
}

void	wall_distance(t_mlx_data *data)
{
	if (data->ray.side == 0)
	{
		data->ray.prep_wall_dist = (data->ray.map_x - data->player.pos_x
				+ (1 - data->ray.step_x) / 2) / data->ray.ray_dir_x;
		data->ray.wall_x = data->player.pos_y
			+ data->ray.prep_wall_dist * data->ray.ray_dir_y;
		if (data->ray.ray_dir_x > 0)
			data->ray.tex_num = 2;
		else
			data->ray.tex_num = 3;
	}
	else
	{
		data->ray.prep_wall_dist = (data->ray.map_y - data->player.pos_y
				+ (1 - data->ray.step_y) / 2) / data->ray.ray_dir_y;
		data->ray.wall_x = data->player.pos_x
			+ data->ray.prep_wall_dist * data->ray.ray_dir_x;
		if (data->ray.ray_dir_y > 0)
			data->ray.tex_num = 1;
		else
			data->ray.tex_num = 0;
	}
	data->ray.wall_x -= floor(data->ray.wall_x);
}

void	wall_height(t_mlx_data *data)
{
	data->ray.line_height = (int)(HEIGHT / data->ray.prep_wall_dist);
	data->ray.draw_start = -data->ray.line_height / 2 + HEIGHT / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height / 2 + HEIGHT / 2;
	if (data->ray.draw_end >= HEIGHT)
		data->ray.draw_end = HEIGHT -1;
}
