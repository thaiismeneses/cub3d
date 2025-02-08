/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:01:32 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/27 12:01:32 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int verify_location(char **map, int i, int j)
{

	if ((i > 0 && (map[i - 1][j] == '1' || map[i - 1][j] == ' ')) ||
		(j > 0 && (map[i][j - 1] == '1' || map[i][j - 1] == ' ')) ||
		(map[i][j + 1] == '1' || map[i][j + 1] == ' ') ||
		(map[i + 1] && (map[i + 1][j] == '1' || map[i + 1][j] == ' ')))
		return (1);
	return (0);
}

static int get_max_width(char **map)
{
	int max_width;
	int width;
	int i;

	max_width = 0;
	i = 0;
	if (!map)
		return (0);
	while (map[i] != NULL)
	{
		width = ft_strlen(map[i]);
		if (width > max_width)
		max_width = width;
		i++;
	}
	return (max_width);
}

static char **fill_zeros(char **map)
{
	int i;
	int j;
	int max_width;
	int num_rows;
	char **new_map;

	i = 0;
	num_rows = 0;
	max_width = get_max_width(map);
	while (map[num_rows])
		num_rows++;
	new_map = calloc((num_rows + 1), sizeof(char *)); // +1 for NULL
	if (!new_map)
		return (NULL);
	while (i < num_rows)
	{
		new_map[i] = calloc((max_width + 1), sizeof(char)); // +1 for '\0'
		if (!new_map[i])
			return (NULL);
		ft_memset(new_map[i], '0', max_width);
		new_map[i][max_width] = '\0';
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == ' ')
			{
				if (verify_location(map, i, j) == 1)
					new_map[i][j] = '0';
				else
					new_map[i][j] = ' ';
			}
			else if (map[i][j] <= 13)
				new_map[i][j] = '0';
			else
				new_map[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	new_map[num_rows] = NULL;
	return (new_map);
}

int valid_wall(t_mlx_data *data)
{
	int i;
	char **map;
	char **new_map;

	i = 0;
	data->map = map_to_matrix(data->tokens);
	new_map = fill_zeros(data->map);
	map = make_portrat(new_map);
	free_matrix(map);
	free_matrix(new_map);
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	return (NONE_ERROR);
}
