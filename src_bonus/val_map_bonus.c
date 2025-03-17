/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:31:22 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/25 10:31:22 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

int	valid_player(t_token *tokens)
{
	int player;
	int i;
	t_token *current;

	player = 0;
	current = tokens;
	while(current != NULL)
	{
		if (current->type == MAP)
		{
			i = 0;
			while (current->data[i] != '\0')
			{
				if (current->data[i] == 'N' || current->data[i] == 'S'
					|| current->data[i] == 'W' || current->data[i] == 'E')
					player++;
				i++;
			}
		}
		current = current->next;
	}
	if (player == 0 || player > 1)
		return (MAP_ERROR);
	return(NONE_ERROR);
}

int	valid_char(t_token *tokens)
{
	int i;
	t_token *current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == MAP)
		{
			i = 0;
			while (current->data[i] != '\0')
			{
				if (current->data[i] != '0' && current->data[i] != '1'
				&& current->data[i] != 'N' && current->data[i] != 'S'
				&& current->data[i] != 'E' && current->data[i] != 'W'
				&& current->data[i] != ' ' && current->data[i] >= 14
				&& current->data[i] != 'D')
				{
					return (MAP_ERROR);
				}
				i++;
			}
		}
		current = current->next;
	}
	return (NONE_ERROR);
}

int	break_map(t_token *tokens)
{
	int	map_found;
	int	map_ended;
	t_token	*current;

	current = tokens;
	map_found = 0;
	map_ended = 0;
	while (current != NULL)
	{
		if (current->type == MAP)
		{
			if (map_ended)
				return (MAP_ERROR);
			map_found = 1;
		}
		else if (current->type == NONE)
		{
			if (map_found)
				map_ended = 1;
		}
		current = current->next;
	}
	return (NONE_ERROR);
}

int	map_exist(t_token *tokens)
{
	int count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == MAP)
			count++;
		if (count > 0)
			return (NONE_ERROR);
		current = current->next;
	}
	return (TEXTURE_ERROR);
}
