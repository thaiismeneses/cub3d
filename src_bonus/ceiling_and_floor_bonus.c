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

#include "../includes_bonus/cub3d_bonus.h"

void	set_direction_ray(t_mlx_data *data)
{
	data->floor_ceiling.ray_dir_x0 = data->player.dir_x - data->player.plane_x;
	data->floor_ceiling.ray_dir_y0 = data->player.dir_y - data->player.plane_y;
	data->floor_ceiling.ray_dir_x1 = data->player.dir_x + data->player.plane_x;
	data->floor_ceiling.ray_dir_y1 = data->player.dir_y + data->player.plane_y;
}

void	dist_to_window(t_mlx_data *data, t_floor_ceiling *fc, int y, int flag)
{
	fc->pos_cur_y = y - 539 ;
	fc->hight_player = 0.5 * HEIGHT;
	if (flag == 0)
	{
		fc->current_dist = fc->hight_player / fc->pos_cur_y;
		fc->floor_step_x = fc->current_dist
			* (fc->ray_dir_x1 - fc->ray_dir_x0) / WIDTH;
		fc->floor_step_y = fc->current_dist
			* (fc->ray_dir_y1 - fc->ray_dir_y0) / WIDTH;
		fc->floor_x = data->player.pos_x + fc->current_dist * fc->ray_dir_x0;
		fc->floor_y = data->player.pos_y + fc->current_dist * fc->ray_dir_y0;
	}
	else
	{
		fc->current_dist = fc->hight_player / (fc->pos_cur_y);
		fc->ceiling_step_x = fc->current_dist
			* (fc->ray_dir_x1 - fc->ray_dir_x0) / WIDTH;
		fc->ceiling_step_y = fc->current_dist
			* (fc->ray_dir_y1 - fc->ray_dir_y0) / WIDTH;
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
					* (fc->ceiling_x - cell_x)))
			% (data->textures[4].width - 1);
		fc->tex_ceiling_y = (int)((data->textures[4].height
					* (fc->ceiling_y - cell_y)))
			% (data->textures[4].height - 1);
	}
}

int	color_ceiling_floor(t_mlx_data *data, int flag)
{
	int	x;
	int	y;

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
