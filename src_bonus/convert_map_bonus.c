/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 20:33:41 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/24 20:33:41 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	check_position(t_mlx_data *data, int i, int j)
{
	if (data->map[i][j] == '1')
		data->map_int[i][j] = 1;
	else if (data->map[i][j] == 'D')
		data->map_int[i][j] = 2;
	else if (data->map_int[i][j] == 'O')
		data->map_int[i][j] = 3;
	else
		data->map_int[i][j] = 0;
}

void	convert_map(t_mlx_data *data)
{
	int	i;
	int	j;
	int	rows;
	int	len;

	i = 0;
	rows = 0;
	while (data->map[rows])
		rows++;
	data->map_int = ft_calloc(rows + 1, sizeof(int *));
	while (i < rows)
	{
		len = ft_strlen(data->map[i]);
		data->map_int[i] = ft_calloc(len, sizeof(int));
		j = 0;
		while (j < len)
		{
			check_position(data, i, j);
			j++;
		}
		i++;
	}
}
