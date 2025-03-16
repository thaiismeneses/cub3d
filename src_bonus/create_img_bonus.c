/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 22:37:29 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/28 10:41:30 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_put_pixel(t_img *img, int x, int y, int color)
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
	int tex_x;
	int tex_y;

	tex_x = (int)(data->ray.wall_x * data->textures[data->ray.tex_num].width);
	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
		tex_x = data->textures[data->ray.tex_num].width - tex_x -1;
	if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		tex_x = data->textures[data->ray.tex_num].width - tex_x -1;
	data->ray.step = 1.0 * data->textures[data->ray.tex_num].height / data->ray.line_height;
	data->ray.tex_pos = (data->ray.draw_start - HEIGHT / 2 + data->ray.line_height / 2) * data->ray.step;
	y = data->ray.draw_start;
	while (y < data->ray.draw_end)
	{
		tex_y = (int)data->ray.tex_pos;
		if (tex_y >= data->textures[data->ray.tex_num].height)
			tex_y = data->textures[data->ray.tex_num].height - 1;
		data->ray.tex_pos += data->ray.step;
		color = *((int *)(data->textures[data->ray.tex_num].addr +
			(tex_y * data->textures[data->ray.tex_num].line_length + tex_x * (data->textures[data->ray.tex_num].bits_per_pixel / 8))));
		my_put_pixel(&data->img, x, y, color);
		y++;
	}
}

void	ray_casting(t_mlx_data *data)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		set_values(data, x);
		set_ray_direction(data);
		algorithm_dda(data);
		wall_distance(data);
		wall_height(data);
		draw_vertical_line(data, x);
		x++;
	}
}

void	render(t_mlx_data *data)
{
	if (!data->textures[0].img)
	load_texture(data);
	create_image(data);
	draw_ceiling_floor(data);
	ray_casting(data);
	update_animation(data);
	render_animation(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx, data->img.img);
}
