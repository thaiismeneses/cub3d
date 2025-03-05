/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:22:07 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/24 10:53:56 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rotate_left(t_mlx_data *data, int keycode)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == XK_Left)
	{
		old_dir_x = data->player.dir_x;
		old_plane_x = data->player.plane_x;
		data->player.dir_x = data->player.dir_x * cos(-ROTATE)
			- data->player.dir_y * sin(-ROTATE);
		data->player.dir_y = old_dir_x * sin(-ROTATE)
			+ data->player.dir_y * cos(-ROTATE);
		data->player.plane_x = data->player.plane_x * cos(-ROTATE)
			- data->player.plane_y * sin(-ROTATE);
		data->player.plane_y = old_plane_x * sin(-ROTATE)
			+ data->player.plane_y * cos(-ROTATE);
	}
}

static void	rotate_right(t_mlx_data *data, int keycode)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == XK_Right)
	{
		old_dir_x = data->player.dir_x;
		old_plane_x = data->player.plane_x;
		data->player.dir_x = data->player.dir_x * cos(ROTATE)
			- data->player.dir_y * sin(ROTATE);
		data->player.dir_y = old_dir_x * sin(ROTATE)
			+ data->player.dir_y * cos(ROTATE);
		data->player.plane_x = data->player.plane_x * cos(ROTATE)
			- data->player.plane_y * sin(ROTATE);
		data->player.plane_y = old_plane_x * sin(ROTATE)
			+ data->player.plane_y * cos(ROTATE);
	}
}

static void	moviments_front_back(t_mlx_data *data, int keycode)
{
	double	move_x;
	double	move_y;

	move_x = data->player.dir_x * MOVE_SPEED;
	move_y = data->player.dir_y * MOVE_SPEED;
	if (keycode == XK_w)
	{
		if (is_valid_position(data, data->player.pos_x + move_x, data->player.pos_y))
			data->player.pos_x += move_x;
		if (is_valid_position(data, data->player.pos_x, data->player.pos_y + move_y))
			data->player.pos_y += move_y;

	}
	if (keycode == XK_s)
	{
		if (is_valid_position(data, data->player.pos_x - move_x, data->player.pos_y))
			data->player.pos_x -=  move_x;
		if (is_valid_position(data, data->player.pos_x, data->player.pos_y - move_y))
			data->player.pos_y -=  move_y;
	}

}

static void	moviments_left_right(t_mlx_data *data, int keycode)
{
	double	move_x;
	double	move_y;

	move_x = data->player.plane_x * MOVE_SPEED;
	move_y = data->player.plane_y * MOVE_SPEED;
	if (keycode == XK_a)
	{
		if (is_valid_position(data, data->player.pos_x - move_x, data->player.pos_y))
			data->player.pos_x -= move_x;
		if (is_valid_position(data, data->player.pos_x, data->player.pos_y - move_y))
			data->player.pos_y -= move_y;
	}
	if (keycode == XK_d)
	{
		if (is_valid_position(data, data->player.pos_x + move_x, data->player.pos_y))
			data->player.pos_x += move_x;
		if (is_valid_position(data, data->player.pos_x, data->player.pos_y + move_y))
			data->player.pos_y += move_y;
	}
}

void	moviments(t_mlx_data *data, int keycode)
{
	moviments_front_back(data, keycode);
	moviments_left_right(data, keycode);
	rotate_right(data, keycode);
	rotate_left(data, keycode);
}
