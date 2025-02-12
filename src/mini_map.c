/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:41:26 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/12 19:15:46 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void draw_square(t_mlx_data *data, int x, int y, int color)
{
	int i, j;
	int tile_size = 10; // Define o tamanho dos blocos do minimapa

	for (i = 0; i < tile_size; i++)
	{
		for (j = 0; j < tile_size; j++)
		{
			mlx_pixel_put(data->mlx, data->win, x + i, y + j, color);
		}
	}
}

void draw_minimap(t_mlx_data *data)
{
	int x, y;
	int tile_size = 10; // Tamanho dos blocos do minimapa
	int start_x = 20;   // Posição inicial do minimapa na tela (ajuste conforme necessário)
	int start_y = 20;

	for (y = 0; data->map[y]; y++)
	{
		for (x = 0; data->map[y][x]; x++)
		{
			if (data->map[y][x] == '1') // Paredes
				draw_square(data, start_x + x * tile_size, start_y + y * tile_size, 0xFFFFFF);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'N') // Caminho ou jogador
				draw_square(data, start_x + x * tile_size, start_y + y * tile_size, 0x333333);
		}
	}

	// Desenhar o jogador no minimapa
	int player_x = start_x + (data->player.pos_x * tile_size);
	int player_y = start_y + (data->player.pos_y * tile_size);
	draw_square(data, player_x, player_y, 0xFF0000); // Vermelho para o jogador
}

