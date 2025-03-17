/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:38:52 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/17 11:02:31 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->endian = 0;
	img->line_length = 0;
}

void	init_textures(t_texture *texture)
{
	texture->img = NULL;
	texture->addr = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bits_per_pixel = 0;
	texture->line_length = 0;
	texture->endian = 0;
}

void	init_floor_ceiling(t_floor_ceiling *floor_ceiling)
{
	floor_ceiling->floor_x = 0.0;
	floor_ceiling->floor_y = 0.0;
	floor_ceiling->tex_floor_x = 0;
	floor_ceiling->tex_floor_y = 0;
	floor_ceiling->ceiling_x = 0.0;
	floor_ceiling->ceiling_y = 0.0;
	floor_ceiling->tex_ceiling_x = 0;
	floor_ceiling->tex_ceiling_y = 0;
	floor_ceiling->current_dist = 0.0;
	floor_ceiling->floor_step_x = 0.0;
	floor_ceiling->floor_step_y = 0.0;
	floor_ceiling->ceiling_step_x = 0.0;
	floor_ceiling->ceiling_step_y = 0.0;
	floor_ceiling->ray_dir_x0 = 0.0;
	floor_ceiling->ray_dir_y0 = 0.0;
	floor_ceiling->ray_dir_x1 = 0.0;
	floor_ceiling->ray_dir_y1 = 0.0;
	floor_ceiling->pos_cur_y = 0;
	floor_ceiling->hight_player = 0.0;
}

void	init_ray(t__ray *ray)
{
	ray->camera_x = 0.0;
	ray->ray_dir_x = 0.0;
	ray->ray_dir_y = 0.0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->delta_dist_x = 0.0;
	ray->delta_dist_y = 0.0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side_dist_x = 0.0;
	ray->side_dist_y = 0.0;
	ray->side = 0;
	ray->prep_wall_dist = 0.0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->wall_x = 0.0;
	ray->tex_num = 0;
}

void	init_data(t_mlx_data *data)
{
	int	i;

	i = -1;
	data->mlx = NULL;
	data->win = NULL;
	data->tokens = NULL;
	init_player(&data->player);
	init_ray(&data->ray);
	init_floor_ceiling(&data->floor_ceiling);
	init_img(&data->img);
	while (i++ < 6)
		init_textures(&data->textures[i]);
	data->map = NULL;
	data->map_frame = NULL;
	data->map_int = NULL;
	init_animation(&data->animation);
	data->mouse_rotation = 0;
}
