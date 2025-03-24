/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:27:17 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/24 20:31:04 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

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
