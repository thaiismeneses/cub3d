/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_and_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:29:41 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/16 20:25:56 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	dist_to_window(t_mlx_data *data, int y, int flag)
{
	if (flag == 0)
	{
		data->floor_ceiling.current_dist = (double)1.0 / (y - HEIGHT / 2);
		data->floor_ceiling.floor_x = data->player.pos_x
			+ data->floor_ceiling.current_dist
			* (data->player.dir_x + data->player.plane_x);
		data->floor_ceiling.floor_y = data->player.pos_y
			+ data->floor_ceiling.current_dist
			* (data->player.dir_y + data->player.plane_y);
	}
	else
	{
		data->floor_ceiling.current_dist = (double)1.0 / (HEIGHT / 2 - y);
		data->floor_ceiling.floor_x = data->player.pos_x
			+ data->floor_ceiling.current_dist
			* (data->player.dir_x - data->player.plane_x);
		data->floor_ceiling.floor_y = data->player.pos_y
			+ data->floor_ceiling.current_dist
			* (data->player.dir_y - data->player.plane_y);
	}
}

void	textures_ceiling_floor(t_mlx_data *data, int flag)
{
	if (flag == 0)
	{
		data->floor_ceiling.tex_floor_x = (int)(data->floor_ceiling.floor_x
				* data->textures[5].width) % data->textures[5].width;
		data->floor_ceiling.tex_floor_y = (int)(data->floor_ceiling.floor_y
				* data->textures[5].height) % data->textures[5].height;
	}
	else
	{
		data->floor_ceiling.tex_ceiling_x = (int)(data->floor_ceiling.ceiling_x
				* data->textures[4].width) % data->textures[4].width;
		data->floor_ceiling.tex_ceiling_y = (int)(data->floor_ceiling.ceiling_y
				* data->textures[4].height) % data->textures[4].height;
	}
}

int	color_ceiling_floor(t_mlx_data *data, int flag)
{
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
	while (y < HEIGHT)
	{
		dist_to_window(data, y, 0);
		x = 0;
		while (x < WIDTH)
		{
			textures_ceiling_floor(data, 0);
			color_floor = color_ceiling_floor(data, 0);
			my_put_pixel(&data->img, x, y, color_floor);
			dist_to_window(data, y, 1);
			textures_ceiling_floor(data, 1);
			color_ceiling = color_ceiling_floor(data, 1);
			my_put_pixel(&data->img, x, HEIGHT - y - 1, color_ceiling);
			x++;
		}
		y++;
	}
}
