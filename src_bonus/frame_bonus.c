/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:57:55 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/09 11:35:12 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static int columns_lines(char **map, t_portrat *portrat)
{
	int i;
	size_t len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			len--;
		if (portrat->columns < len)
			portrat->columns = len;
		i++;
	}
	portrat->lines = i + 4;
	portrat->columns = portrat->columns + 4;
	return (i);
}

static void malloc_line(t_portrat *portrat, size_t i)
{
	portrat->map_portrat[i] = malloc(portrat->columns + 2);
	if (!portrat->map_portrat[i])
	{
		while (i > 0)
			free(portrat->map_portrat[--i]);
		free(portrat->map_portrat);
	}
}

void	put_on_portrat(char **map, t_portrat *portrat, size_t i, size_t j)
{
	size_t original_len;

	if (i < 2 || i >= portrat->lines - 2 || j < 2 || j >= portrat->columns - 2)
	{
		if (i == 0 || i == portrat->lines - 1 || j == 0 || j == portrat->columns - 1)
			portrat->map_portrat[i][j] = '1';
		else
			portrat->map_portrat[i][j] = '0';
	}
	else
	{
		original_len = ft_strlen(map[i - 2]);
		if (map[i - 2][original_len - 1] == '\n')
			original_len--;
		if (j - 2 < original_len)
			portrat->map_portrat[i][j] = map[i - 2][j - 2];
		else
			portrat->map_portrat[i][j] = '0';
	}
}

char	**make_portrat(char **map)
{
	size_t i;
	size_t j;
	t_portrat	portrat;

	init_portrat(&portrat);
	i = columns_lines(map, &portrat);
	portrat.map_portrat = malloc((portrat.lines + 1) * sizeof(char *));
	if (!portrat.map_portrat)
		return (NULL);
	i = 0;
	while (i < portrat.lines)
	{
		malloc_line(&portrat, i);
		j = 0;
		while (j < portrat.columns)
		{
			put_on_portrat(map, &portrat, i, j);
			j++;
		}
		portrat.map_portrat[i][j] = '\n';
		portrat.map_portrat[i][j + 1] = '\0';
		i++;
	}
	portrat.map_portrat[portrat.lines] = NULL;
	return (portrat.map_portrat);
}
static int	height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static int	width(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j] != '\0' && map[i][j] != '\n')
		j++;
	return (j);
}

static void	xy_player(char **map, t_map *map_copy)
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

t_map	*struct_map(char **map)
{
	t_map	*copy_map;

	copy_map = ft_calloc(1, sizeof(t_map));
	if (!copy_map)
		return (NULL);
	copy_map->map = map;
	copy_map->height = height(map);
	copy_map->width = width(map);
	xy_player(map, copy_map);
	return (copy_map);
}
static void	fill_map(t_map *copy_map, int x, int y)
{
	if (x < 0 || x >= copy_map->width || y < 0 || y >= copy_map->height)
		return;
	if (copy_map->map[y][x] == '1')
		return;
	copy_map->map[y][x] = '1';
	fill_map(copy_map, x - 1, y);
	fill_map(copy_map, x + 1, y);
	fill_map(copy_map, x, y - 1);
	fill_map(copy_map, x, y + 1);
}

static int valid_map(t_map *copy_map)
{
	int x;
	int y;

	x = copy_map->x_player;
	y = copy_map->y_player;
	if (!copy_map || !copy_map->map)
		return (MAP_ERROR);
	if (copy_map->map[y - 1][x] == '1' && copy_map->map[y + 1][x] == '1' &&
		copy_map->map[y][x - 1] == '1' && copy_map->map[y][x + 1] == '1')
		return (MAP_ERROR);
	return(NONE_ERROR);
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
