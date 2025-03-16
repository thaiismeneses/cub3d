/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:26:59 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/16 19:01:01 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_animation(t_mlx_data *data)
{
	int		i;
	char	*texture_files[4];

	i = -1;
	texture_files[0] = "assets/JellyFish-1.xpm";
	texture_files[1] = "assets/JellyFish-2.xpm";
	texture_files[2] = "assets/JellyFish-3.xpm";
	texture_files[3] = "assets/JellyFish-4.xpm";
	data->animation.current_frame = 0;
	data->animation.frame_time = 0;
	while (i++ < 3)
	{
		data->animation.jf[i].img = mlx_xpm_file_to_image(data->mlx,
				texture_files[i], &data->animation.jf[i].width,
				&data->animation.jf[i].height);
		data->animation.jf[i].addr = mlx_get_data_addr(
				data->animation.jf[i].img,
				&data->animation.jf[i].bits_per_pixel,
				&data->animation.jf[i].line_length,
				&data->animation.jf[i].endian);
	}
}

void	update_animation(t_mlx_data *data)
{
	int	i;

	data->animation.frame_time++;
	if (data->animation.frame_time >= 10)
	{
		data->animation.current_frame = (data->animation.current_frame + 1) % 4;
		data->animation.frame_time = 0;
	}
	i = 0;
	while (i < NUM_JELLYFISH)
	{
		data->animation.multi_offset_x[i] += 3;
		if (data->animation.multi_offset_x[i] > WIDTH)
			data->animation.multi_offset_x[i] = -WIDTH;
		i++;
	}
}

void	draw_scaled_pixel(t_mlx_data *data, t_point base, int scale, int color)
{
	int	dx;
	int	dy;

	dx = 0;
	while (dx < scale)
	{
		dy = 0;
		while (dy < scale)
		{
			my_put_pixel(&data->img, base.x + dx, base.y + dy, color);
			dy++;
		}
		dx++;
	}
}

void	draw_jellyfish_instance(t_mlx_data *data, t_point jelly_pos,
			t_texture current, int scale)
{
	int			x;
	int			y;
	int			color;
	t_point		base;

	x = 0;
	while (x < current.width)
	{
		y = 0;
		while (y < current.height)
		{
			color = *(unsigned int *)(current.addr
					+ ((current.width * y + x) * 4));
			if ((color & 0x00FFFFFF) != 0)
			{
				{
					base.x = jelly_pos.x + x * scale;
					base.y = jelly_pos.y + y * scale;
					draw_scaled_pixel(data, base, scale, color);
				}
			}
			y++;
		}
		x++;
	}
}

t_point	calculate_jellyfish_position(t_mlx_data *data, int i,
		t_texture current, int scale)
{
	t_point		pos;

	pos.x = (WIDTH - current.width * scale) / 2
		+ data->animation.multi_offset_x[i] + (i * 150);
	if (i == 0)
	{
		pos.y = (HEIGHT - current.height * scale) / 2 - 50;
	}
	else if (i == 2)
	{
		pos.y = (HEIGHT - current.height * scale) / 2 + 50;
	}
	else
	{
		pos.y = (HEIGHT - current.height * scale) / 2;
	}
	return (pos);
}

void	render_animation(t_mlx_data *data)
{
	int			i;
	int			scale;
	t_texture	current;
	t_point		pos;

	i = 0;
	scale = 4;
	current = data->animation.jf[data->animation.current_frame];
	while (i < NUM_JELLYFISH)
	{
		pos = calculate_jellyfish_position(data, i, current, scale);
		draw_jellyfish_instance(data, pos, current, scale);
		i++;
	}
}
