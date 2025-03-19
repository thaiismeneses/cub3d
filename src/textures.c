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

#include "../includes/cub3d.h"

void get_rgb_color_to_hex(t_mlx_data *data)
{
	t_token *current;
	char **f_rgb;
	char **c_rgb;

	current = data->tokens;
	while (current != NULL)
	{
		if (current->type == F)
		{
			f_rgb = ft_split(current->data, ',');
			data->f_color = ft_atoi(f_rgb[0]) << 16 \
							| ft_atoi(f_rgb[1]) << 8 \
            				| ft_atoi(f_rgb[2]);
			free_matrix(f_rgb);
		}
		else if (current->type == C)
		{
			c_rgb = ft_split(current->data, ',');
			data->c_color = ft_atoi(c_rgb[0]) << 16 \
							| ft_atoi(c_rgb[1]) << 8 \
							| ft_atoi(c_rgb[2]);
			free_matrix(c_rgb);
		}
		current = current->next;
	}
}

int is_valid_number(char **rgb)
{
	int i;
	int number;

	i = 0;
	while (rgb[i])
	{
		number = ft_atoi(rgb[i]);
		if (number < 0 || number > 255)
			return (free(rgb), COLOR_ERROR);
		i++;
	}
	if (i != 3)
		return (free(rgb), COLOR_ERROR);
	return (NONE_ERROR);
}

int	rgb_textures(t_token *tokens)
{
	char	**rgb;
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == F || current->type == C)
		{
			rgb = ft_split(current->data, ',');
			if (rgb == NULL)
				return (COLOR_ERROR);
			if (is_valid_number(rgb) == COLOR_ERROR)
				return (COLOR_ERROR);
			free_matrix(rgb);
		}
		current = current->next;
	}
	return (NONE_ERROR);
}

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
			|| current->type == WE || current->type == EA)
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
	while (i++ < 5)
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
