/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:22:14 by thfranco          #+#    #+#             */
/*   Updated: 2025/01/29 09:22:31 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void	free_list(t_token *token)
{
	t_token	*current;
	t_token *temp;
	if(!token)
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
	while (matrix[i])
		i++;
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
}

int	free_game(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free_list(data->tokens);
	free(data->mlx);
	exit(0);
}
