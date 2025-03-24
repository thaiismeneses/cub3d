/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:45:34 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/25 10:45:34 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	is_valid_file_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (PATH_ERROR);
	close(fd);
	return (NONE_ERROR);
}

int	xpm_file(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == NO || current->type == SO
			|| current->type == WE || current->type == EA || current->type == DR)
		{
			if (check_extension(current->data, ".xpm") == EXTENSION_ERROR
				|| is_valid_file_path(current->data) == PATH_ERROR)
				return (PATH_ERROR);
		}
		current = current->next;
	}
	return (NONE_ERROR);
}

static char *get_texture_path(t_mlx_data *data, int flag)
{
	t_token	*current;

	current = data->tokens;
	while (current && current->next != NULL)
	{
		if (current->type == 0 && flag == 0)
			return (current->data);
		if (current->type == 1 && flag == 1)
			return (current->data);
		if (current->type == 2 && flag == 2)
			return (current->data);
		if (current->type == 3 && flag == 3)
			return (current->data);
		if (current->type == 8 && flag == 8)
			return (current->data);
		current = current->next;
	}
	return (NULL);
}

void	load_texture(t_mlx_data *data)
{
	int		i;
	char	*texture_files[6];

	i = -1;
	texture_files[0] = get_texture_path(data, 0);
	texture_files[1] = get_texture_path(data, 1);
	texture_files[2] = get_texture_path(data, 2);
	texture_files[3] = get_texture_path(data, 3);
	texture_files[4] = "assets/sky.xpm";
	texture_files[5] = "assets/sand.xpm";
	texture_files[6] = get_texture_path(data, 8);
	while (i++ < 6)
	{
		data->textures[i].img = mlx_xpm_file_to_image(data->mlx,
				texture_files[i],
				&data->textures[i].width, &data->textures[i].height);
		if (!data->textures[i].img)
		{
			printf("Error\nTexture file not found\n");
			exit(1);
		}
		data->textures[i].addr = mlx_get_data_addr(data->textures[i].img,
				&data->textures[i].bits_per_pixel,
				&data->textures[i].line_length, &data->textures[i].endian);
	}
}
