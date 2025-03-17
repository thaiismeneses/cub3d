/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:34:51 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/12 22:15:07 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

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
			if (data->map[i][j] == '1')
				data->map_int[i][j] = 1;
			else
				data->map_int[i][j] = 0;
			j++;
		}
		i++;
	}
}
