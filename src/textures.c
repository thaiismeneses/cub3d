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

int	rgb_textures(t_token *tokens)
{
	int i;
	int number;
	char **rgb;
	t_token	*current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == F || current->type == C)
		{
			rgb = ft_split(current->data, ',');
			if (rgb == NULL)
				return (COLOR_ERROR);
			i = 0;
			while(rgb[i])
			{
				number = ft_atoi(rgb[i]);
				if (number < 0 || number > 255)
					return (free(rgb), COLOR_ERROR);
				i++;
			}
			if (i != 3)
				return (free(rgb), COLOR_ERROR);
			free_matrix(rgb);
		}
		current = current->next;
	}
	return (NONE_ERROR);
}

int	is_valid_file_path(char *path)
{
	int fd;

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
