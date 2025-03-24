/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playable_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:14:21 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/03/24 16:25:38 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	xy_player(char **map, t_map *map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i] && map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'S' || map[i][j] == 'E')
			{
				map_copy->x_player = j;
				map_copy->y_player = i;
				break ;
			}
			j++;
		}
		i++;
	}
}

static void	fill_map(t_map *copy_map, int x, int y)
{
	if (x < 0 || x >= copy_map->width || y < 0 || y >= copy_map->height)
		return ;
	if (copy_map->map[y][x] == '1')
		return ;
	copy_map->map[y][x] = '1';
	fill_map(copy_map, x - 1, y);
	fill_map(copy_map, x + 1, y);
	fill_map(copy_map, x, y - 1);
	fill_map(copy_map, x, y + 1);
}

static int	valid_map(t_map *copy_map)
{
	int	x;
	int	y;

	x = copy_map->x_player;
	y = copy_map->y_player;
	if (!copy_map || !copy_map->map)
		return (MAP_ERROR);
	if (copy_map->map[y - 1][x] == '1' && copy_map->map[y + 1][x] == '1' &&
		copy_map->map[y][x - 1] == '1' && copy_map->map[y][x + 1] == '1')
		return (MAP_ERROR);
	return (NONE_ERROR);
}

int	playable_map(t_mlx_data *data)
{
	t_map	*copy_map;

	copy_map = struct_map(data->map_frame);
	fill_map(copy_map, 1, 1);
	if (valid_map(copy_map) == MAP_ERROR)
	{
		free_matrix(copy_map->map);
		free(copy_map);
		return (MAP_ERROR);
	}
	free_matrix(copy_map->map);
	free(copy_map);
	return (NONE_ERROR);
}
