/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:35:38 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/23 11:35:38 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	check_extension(char *argv, char *ext)
{
	int		i;
	int		j;

	i = 0;
	j = 3;
	while (argv[i] != '\0')
		i++;
	i--;
	while (j >= 0)
	{
		if (argv[i] != ext[j])
			return (EXTENSION_ERROR);
		i--;
		j--;
	}
	if (i < 0)
		return (EXTENSION_ERROR);
	return (NONE_ERROR);
}

int	error_messages(int error)
{
	ft_putstr_fd("Error\n", 2);
	if (error == -1)
		ft_putstr_fd("Wrong numbers of arguments, expected 2.\n", 2);
	else if (error == -2)
		ft_putstr_fd("Invalid extension path, expected .cub file.\n", 2);
	else if (error == -3)
		ft_putstr_fd("Error opening the map file.\n", 2);
	else if (error == -4)
		ft_putstr_fd("Invalid map.\n", 2);
	else if (error == -5)
		ft_putstr_fd("Invalid scene description.\n", 2);
	else if (error == -6)
		ft_putstr_fd("Invalid texture file.\n", 2);
	else if (error == -7)
		ft_putstr_fd("Invalid RGB colors.\n", 2);
	return (error);
}

int	check_errors(t_mlx_data *data)
{
	if (val_texture(data->tokens) == TEXTURE_ERROR
		|| verify_order(data->tokens) == TEXTURE_ERROR
		|| map_exist(data->tokens) == TEXTURE_ERROR)
		return (error_messages(TEXTURE_ERROR));
	else if (xpm_file(data->tokens) == PATH_ERROR)
		return (error_messages(PATH_ERROR));
	else if (rgb_textures(data->tokens) == COLOR_ERROR)
		return (error_messages(COLOR_ERROR));
	else if (break_map(data->tokens) == MAP_ERROR
		|| valid_char(data->tokens) == MAP_ERROR
		|| valid_player(data->tokens) == MAP_ERROR
		|| valid_wall(data) == MAP_ERROR)
		return (error_messages(MAP_ERROR));
	get_rgb_color_to_hex(data);
	return (NONE_ERROR);
}
