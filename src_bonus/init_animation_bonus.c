/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:41:32 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/17 11:02:25 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	init_animation(t_animation *animation)
{
	int	i;

	i = 0;
	animation->current_frame = 0;
	animation->frame_time = 0;
	animation->offset_x = 0;
	while (i < NUM_JELLYFISH)
	{
		animation->multi_offset_x[i] = 0;
		i++;
	}
}

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
