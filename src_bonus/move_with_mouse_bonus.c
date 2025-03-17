/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_with_mouse_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:55 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/17 11:03:12 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	mouse(int x, int y, t_mlx_data *data)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	(void)y;
	if (!data->mouse_rotation)
		return (0);

	if (x < (WIDTH / 4))
		angle = -((WIDTH / 4) - x) * MOUSE_SPEED;
	else if (x > ((3 * WIDTH) / 4))
		angle = (x - ((3 * WIDTH) / 4)) * MOUSE_SPEED;
	else
		angle = 0;
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(angle) - data->player.dir_y * sin(angle);
	data->player.dir_y = old_dir_x * sin(angle) + data->player.dir_y * cos(angle);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(angle) - data->player.plane_y * sin(angle);
	data->player.plane_y = old_plane_x * sin(angle) + data->player.plane_y * cos(angle);
	if (data->mlx && data->win)
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}

