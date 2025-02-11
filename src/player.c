/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:00:11 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/11 11:40:36 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	find_direction(t_mlx_data *data)
{
	if (data->player.position == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
	}
	else if (data->player.position == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
	}
	else if (data->player.position == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
	}
	else if (data->player.position == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
	}
}

void	find_plane(t_mlx_data *data)
{
	if (data->player.position == 'N')
	{
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.position == 'S')
	{
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.position == 'E')
	{
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (data->player.position == 'W')
	{
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

void	find_player(t_mlx_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[j])
	{
		i = 0;
		while (data->map[j][i])
		{
			if (data->map[j][i] == 'N' || data->map[j][i] == 'S'
				|| data->map[j][i] == 'W' || data->map[j][i] == 'E')
			{
				data->player.position = data->map[j][i];
				data->player.pos_x = (float)i;
				data->player.pos_y = (float)j;
				find_direction(data);
				find_plane(data);
			}
			i++;
		}
		j++;
	}
}
