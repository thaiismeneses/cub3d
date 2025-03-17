/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:00:31 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/30 09:00:31 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

static void	full_matrix(char **matrix, t_token *tokens, int line_count)
{
	int i;
	t_token *current;

	i = 0;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == MAP)
		{
			matrix[i] = ft_strdup(current->data);
			if (i == line_count)
			{
				matrix[i + 1] = NULL;
				break ;
			}
			i++;
		}
		current = current->next;
	}
}

char	**map_to_matrix(t_token *tokens)
{
	int line_count;
	int max_cols;
	int len;
	char **matrix;
	t_token *current;

	current = tokens;
	line_count = 0;
	max_cols = 0;
	while (current != NULL)
	{
		if (current->type == MAP)
		{
			line_count++;
			len = ft_strlen(current->data);
			if (len > max_cols)
				max_cols = len;
		}
		current = current->next;
	}
	matrix = calloc((line_count + 1), sizeof(char *));
	if (!matrix)
		return (NULL);
	full_matrix(matrix, tokens, line_count);
	return (matrix);
}
