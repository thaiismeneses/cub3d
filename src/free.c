/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:22:14 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/18 17:41:47 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_list(t_token *token)
{
	t_token	*current;
	t_token	*temp;

	if (!token)
		return ;
	current = token;
	while (current)
	{
		temp = current->next;
		free(current->data);
		current->data = NULL;
		free(current);
		current = temp;
	}
	token = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		i++;
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
}

void	free_matrix_int(int **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		i++;
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
}

void	free_data_struct(t_mlx_data *data)
{
	free_list(data->tokens);
	free_matrix(data->map);
	free_matrix_int(data->map_int);
	free(data->mlx);
}

int	free_game(t_mlx_data *data)
{
	int	i;

	i = -1;
	while (i++ < 5)
		mlx_destroy_image(data->mlx, data->textures[i].img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free_data_struct(data);
	exit(0);
}
