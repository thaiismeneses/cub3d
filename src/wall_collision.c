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

#include "../includes/cub3d.h"


// int	get_height(t_mlx_data *data)
// {
// 	int	height;

// 	height = 0;
// 	while (data->map_int[height])
// 		height++;
// 	return (height);
// }

// int get_width(int *map_int)
// {
// 	int width;

// 	width = 0;
// 	if (!map_int)
// 		return (0);
// 	while (map_int[width])
// 		width++;
// 	return (width);
// }

// int	is_valid_position(t_mlx_data *data, double new_x, double new_y)
// {
// 	int	x;
// 	int	y;

// 	x = (int)new_x;
// 	y = (int)new_y;
// 	printf("height: %d\n", get_height(data));
// 	printf("width: %d\n", get_width(data->map_int[y]));
// 	if (y < 0 || y >= get_height(data))
// 		return (0);
// 	if (x < 0 || x >= get_width(data->map_int[y]))
// 		return (0);
// 	if (data->map_int[y][x] == 1)
// 		return (0);
// 	return (1);
// }

#define PADDING 0.2 // Pequeno valor para evitar colisões abruptas

int is_valid_position(t_mlx_data *data, double new_x, double new_y)
{
    int x1 = (int)(new_x - PADDING);
    int y1 = (int)(new_y - PADDING);
    int x2 = (int)(new_x + PADDING);
    int y2 = (int)(new_y + PADDING);

    // Verifica se alguma parte do jogador está dentro de uma parede
    if (data->map_int[y1][x1] == 1 || data->map_int[y1][x2] == 1 ||
        data->map_int[y2][x1] == 1 || data->map_int[y2][x2] == 1)
        return (0);

    return (1);
}
