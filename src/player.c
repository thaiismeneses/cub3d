/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:00:11 by thfranco          #+#    #+#             */
/*   Updated: 2025/01/26 21:03:58 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	find_direction(t_mlx_data *data)
{
	if (data->player.position == 'N')
	{
		data->player.dirX = 0;
		data->player.dirY = -1;
	}
	else if (data->player.position == 'S')
	{
		data->player.dirX = 0;
		data->player.dirY = 1;
	}
	else if (data->player.position == 'E')
	{
		data->player.dirX = 1;
		data->player.dirY = 0;
	}
	else if (data->player.position == 'W')
	{
		data->player.dirX = -1;
		data->player.dirY = 0;
	}
}

void	find_plane(t_mlx_data *data)
{
	if (data->player.position == 'N')
	{
		data->player.planeX = 0.66;
		data->player.planeY = 0;
	}
	else if (data->player.position == 'S')
	{
		data->player.dirX = -0.66;
		data->player.dirY = 0;
	}
	else if (data->player.position == 'E')
	{
		data->player.dirX = 0;
		data->player.dirY = 0.66;
	}
	else if (data->player.position == 'W')
	{
		data->player.dirX = 0;
		data->player.dirY = -0.66;
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
				data->player.posX = i;
				data->player.posY = j;
				find_direction(data);
				find_plane(data);
			}
			i++;
		}
		j++;
		data->tokens = data->tokens->next;
	}
}
