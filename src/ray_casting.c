/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:21:58 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/03 22:23:45 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_values(t_mlx_data *data, int x)
{
	//Convertendo as coordenadas da tela para as coordenadas da camera
	data->ray.camera_x = 2 * x / (float)WIDTH - 1;
	/*Calculando a direção do raio (direção para onde o jogador ta olhando)
		raio = direção do jogador + plano da camera * coordenada da camera
	*/
	data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x * data->ray.camera_x;
	data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y * data->ray.camera_x;
	//Posição do jogador no mapa ()
	data->ray.map_x = (int)data->player.pos_x;
	data->ray.map_y = (int)data->player.pos_y;
	//Tamanho do raio entre dois pontos. Calculo o tempo que o raio leva para atravessar um quadrado
	data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
}

void	set_ray_direction(t_mlx_data *data)
{
	//Calculando a direção do raio. Direita/Esquerda e Cima/Baixo
	//Calcula a distancia do raio até a proxima parede
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos_x - data->ray.map_x) * data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos_x) * data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y) * data->ray.side_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos_y) * data->ray.delta_dist_y;
	}
}

void	algoritmo_dda(t_mlx_data *data)
{
	int hit;
	int side;

	hit = 0;
	while (hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			side = 0;
			printf("side: %d\n", side);
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			side = 1;
			printf("side: %d\n", side);
		}
		if (data->map[data->ray.map_y][data->ray.map_x] == '1')
			hit = 1;
	}

}

void	ray_casting(t_mlx_data *data)
{
	int x;

	x = 0;
	while(x	< WIDTH)
	{
		set_values(data, x);
		set_ray_direction(data);
		algoritmo_dda(data);

		// printf("camera_x: %f\n", data->ray.camera_x);
		// printf("ray_dir_x: %f\n", data->ray.ray_dir_x);
		// printf("ray_dir_y: %f\n", data->ray.ray_dir_y);
		// printf("map_x: %d\n", data->ray.map_x);
		// printf("map_y: %d\n", data->ray.map_y);
		// printf("delta_dist_x: %f\n", data->ray.delta_dist_x);
		// printf("delta_dist_y: %f\n\n", data->ray.delta_dist_y);
		// printf("step_x: %d\n", data->ray.step_x);
		// printf("side_dist_x: %f\n", data->ray.side_dist_x);
		// printf("step_y: %d\n", data->ray.step_y);
		// printf("side_dist_y: %f\n", data->ray.side_dist_y);
		x++;
	}
}
