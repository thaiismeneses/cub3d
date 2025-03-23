/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:41:39 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/12 22:28:30 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static void	open_door(t_mlx_data *data, int keycode)
{
	int	front_x;
	int	front_y;

	front_x = (int)(data->player.pos_x + data->player.dir_x);
	front_y = (int)(data->player.pos_y + data->player.dir_y);
	if (keycode == XK_space)
	{
		if (data->map_int[front_y][front_x] == 2  && data->map[front_y][front_x] == 'D')
		{
			data->map_int[front_y][front_x] = 3;
			data->map[front_y][front_x] = 'O';
		}
		else if (data->map_int[front_y][front_x] == 3 && data->map[front_y][front_x] == 'O')
		{
			data->map_int[front_y][front_x] = 2;
			data->map[front_y][front_x] = 'D';
		}
	}
}

int	handle_board(int keycode, t_mlx_data *data)
{
	open_door(data, keycode);
	moviments(data, keycode);
	if (keycode == XK_Escape)
		free_game(data);
	return (0);
}
