/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:26 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/24 09:51:54 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static void	draw_pixel(t_mlx_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_MAP_SCALE)
	{
		j = 0;
		while (j < MINI_MAP_SCALE)
		{
			my_put_pixel(&data->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_mlx_data *data)
{
	int	x;
	int	y;
	int	square_size;

	square_size = MINI_MAP_SCALE;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_pixel(data, MINIMAP_OFFSET_X + x * square_size,
					MINIMAP_OFFSET_Y + y * square_size, WHITE);
			else if (data->map[y][x] == '0')
				draw_pixel(data, MINIMAP_OFFSET_X + x * square_size,
					MINIMAP_OFFSET_Y + y * square_size, BLUE);
			x++;
		}
		y++;
	}
	x = MINIMAP_OFFSET_X + (int)(data->player.pos_x * square_size);
	y = MINIMAP_OFFSET_Y + (int)(data->player.pos_y * square_size);
	draw_pixel(data, x, y, RED);
}
