/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:00:11 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/01 15:14:57 by thfranco         ###   ########.fr       */
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
		data->player.dir_x = -0.66;
		data->player.dir_y = 0;
	}
	else if (data->player.position == 'E')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 0.66;
	}
	else if (data->player.position == 'W')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -0.66;
	}
}
void	find_player(t_mlx_data *data)
{
	int i = 0;
	int j = 0;
	while (data->tokens->type != MAP)
		data->tokens = data->tokens->next;
	while (data->tokens->data && data->tokens->next)
	{
		i = 0;
		while (data->tokens->data[i])
		{
			if (data->tokens->data[i] == 'N' || data->tokens->data[i] == 'S'
				|| data->tokens->data[i] == 'W' || data->tokens->data[i] == 'E')
			{
				data->player.position = data->tokens->data[i];
				data->player.pos_x = i;
				data->player.pos_y = j;
				find_direction(data);
				find_plane(data);
			}
			i++;
		}
		j++;
		data->tokens = data->tokens->next;
	}
}
