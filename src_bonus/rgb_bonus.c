/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:27:39 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/03/27 18:38:54 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_rgb_color_to_hex(t_mlx_data *data)
{
	t_token	*current;
	char	**f_rgb;
	char	**c_rgb;

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

int	is_valid_number(char **rgb)
{
	int	i;
	int	number;
	int	j;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		while (rgb[i][j])
		{
			if (ft_isalpha(rgb[i][j]))
				return (free(rgb), COLOR_ERROR);
			j++;
		}
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
