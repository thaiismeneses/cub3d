/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling_floor_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:39:10 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/24 20:34:36 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	utils_ceiling_floor(t_mlx_data *data, int x, int y)
{
	textures_ceiling_floor(data, &data->floor_ceiling, 0);
	data->floor_ceiling.floor_x += data->floor_ceiling.floor_step_x;
	data->floor_ceiling.floor_y += data->floor_ceiling.floor_step_y;
	data->floor_ceiling.color_floor = color_ceiling_floor(data, 0);
	my_put_pixel(&data->img, x, y, data->floor_ceiling.color_floor);
	textures_ceiling_floor(data, &data->floor_ceiling, 1);
	data->floor_ceiling.ceiling_x += data->floor_ceiling.ceiling_step_x;
	data->floor_ceiling.ceiling_y += data->floor_ceiling.ceiling_step_y;
	data->floor_ceiling.color_ceiling = color_ceiling_floor(data, 1);
	my_put_pixel(&data->img, x, HEIGHT - y - 1,
		data->floor_ceiling.color_ceiling);
}

void	draw_ceiling_floor(t_mlx_data *data)
{
	int	y;
	int	x;

	y = HEIGHT / 2;
	set_direction_ray(data);
	while (y < HEIGHT)
	{
		dist_to_window(data, &data->floor_ceiling, y, 0);
		dist_to_window(data, &data->floor_ceiling, y, 1);
		x = 0;
		while (x < WIDTH)
		{
			utils_ceiling_floor(data, x, y);
			x++;
		}
		y++;
	}
}
