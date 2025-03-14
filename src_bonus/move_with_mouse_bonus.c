/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_with_mouse_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:16:55 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/06 21:31:23 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int	mouse(t_mlx_data *data, int x, int y)
{
	if (y != -1)
		data->ray.ray_dir_x += (x - data->mouse_x) / 3;
	data->mouse_x = x;
	return (0);
}
