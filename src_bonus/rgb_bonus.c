/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:27:39 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/03/24 11:16:36 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_number(char **rgb)
{
	int	i;
	int	number;

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
