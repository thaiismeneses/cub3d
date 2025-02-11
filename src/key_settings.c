/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:41:39 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/11 16:24:07 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void moviment_right(t_mlx_data *data, int keycode)
{
	if (keycode == XK_a)
	{
		float old_dir_x;
		float old_plane_x;

		old_dir_x = data->player.dir_x;
		old_plane_x = data->player.plane_x;
		data->player.dir_x = data->player.dir_x * cos(-ROTATE) - data->player.dir_y * sin(-ROTATE);
		data->player.dir_y = old_dir_x * sin(-ROTATE) + data->player.dir_y * cos(-ROTATE);
		data->player.plane_x = data->player.plane_x * cos(-ROTATE) - data->player.plane_y * sin(-ROTATE);
		data->player.plane_y = old_plane_x * sin(-ROTATE) + data->player.plane_y * cos(-ROTATE);
	}

}

static void moviment_left(t_mlx_data *data, int keycode)
{
	if (keycode == XK_d)
	{
		float old_dir_x;
		float old_plane_x;

		old_dir_x = data->player.dir_x;
		old_plane_x = data->player.plane_x;
		data->player.dir_x = data->player.dir_x * cos(ROTATE) - data->player.dir_y * sin(ROTATE);
		data->player.dir_y = old_dir_x * sin(ROTATE) + data->player.dir_y * cos(ROTATE);
		data->player.plane_x = data->player.plane_x * cos(ROTATE) - data->player.plane_y * sin(ROTATE);
		data->player.plane_y = old_plane_x * sin(ROTATE) + data->player.plane_y * cos(ROTATE);
	}
}

static void moviments_front_back(t_mlx_data *data, int keycode)
{
	if (keycode == XK_w)
	{
		data->player.pos_x += data->player.dir_x * MOVE_SPEED;
		data->player.pos_y += data->player.dir_y * MOVE_SPEED;
	}
	if (keycode == XK_s)
	{
		data->player.pos_x -= data->player.dir_x * MOVE_SPEED;
		data->player.pos_y -= data->player.dir_y * MOVE_SPEED;
	}
}

static void	moviments(int keycode, t_mlx_data *data)
{
	moviments_front_back(data, keycode);
	moviment_right(data, keycode);
	moviment_left(data, keycode);
}

int	handle_board(int keycode, t_mlx_data *data)
{
	moviments(keycode, data);
	if (keycode == XK_Escape)
		free_game(data);
	return (0);
}
