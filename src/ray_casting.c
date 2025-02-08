/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:21:58 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/05 22:04:36 by thfranco         ###   ########.fr       */
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
	//Calcula a distância do raio até a próxima parede
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
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y) * data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos_y) * data->ray.delta_dist_y;
	}
}

void	algorithm_dda(t_mlx_data *data)
{
	int hit;

	hit = 0;
	//Encontra uma parede
	while (hit == 0)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->map[data->ray.map_y][data->ray.map_x] == '1')
			hit = 1;
	}

}

void	wall_distance(t_mlx_data *data)
{
	//Calcula a distância perpendicular do jogador até a parede
	//Corrigir a distorção da perespectiva, tamanho das paredes corretas na tela
	if (data->ray.side == 0)
		data->ray.prep_wall_dist = (data->ray.map_x - data->player.pos_x +
			(1 - data->ray.step_x) / 2) / data->ray.ray_dir_x;
	else
		data->ray.prep_wall_dist = (data->ray.map_y - data->player.pos_y +
			(1 - data->ray.step_y) / 2) / data->ray.ray_dir_y;
}
void	wall_height(t_mlx_data *data)
{
	int line_height;

	line_height = (int)(HEIGHT / data->ray.prep_wall_dist);
	data->ray.draw_start = -line_height / 2 + HEIGHT / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = line_height / 2 + HEIGHT / 2;
	if (data->ray.draw_end >= HEIGHT)
		data->ray.draw_end = HEIGHT -1;
}

void my_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;

}

void	create_image(t_mlx_data *data)
{
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
	{
		printf("Error creating image");
		return ;
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
		&data->img.line_length, &data->img.endian);
	if (!data->img.addr)
	{
		printf("Error getting image address");
		return ;
	}
}

void draw_vertical_line(t_mlx_data *data, int x)
{
	int color;
	int y;

	y = data->ray.draw_start;
	if (data->ray.side == 0)
		color = 0xFFFFFF;
	else
		color = 0xAAAAAA;
	while (y < data->ray.draw_end)
	{
		my_put_pixel(&data->img, x, y, color);
		y++;
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
		algorithm_dda(data);
		wall_distance(data);
		wall_height(data);
		draw_vertical_line(data,x);
		x++;
	}
}


void	render(t_mlx_data *data)
{
	create_image(data);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
}
