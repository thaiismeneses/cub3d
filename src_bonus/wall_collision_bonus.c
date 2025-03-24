/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:48:31 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/24 10:47:19 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	is_valid_position(t_mlx_data *data, double new_x, double new_y)
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;

	x1 = (int)(new_x - PADDING);
	y1 = (int)(new_y - PADDING);
	x2 = (int)(new_x + PADDING);
	y2 = (int)(new_y + PADDING);
	if (data->map_int[y1][x1] == 1 || data->map_int[y1][x2] == 1 ||
		data->map_int[y2][x1] == 1 || data->map_int[y2][x2] == 1 ||
		data->map_int[y1][x1] == 2 || data->map_int[y1][x2] == 2 ||
		data->map_int[y2][x1] == 2 || data->map_int[y2][x2] == 2)
		return (0);
	return (1);
}
