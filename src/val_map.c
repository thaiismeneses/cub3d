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

#include "../includes/cub3d.h"

int break_map(t_token *tokens)
{
    int map_found;
    int map_ended;
    t_token	*current;

    current = tokens;
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

int map_exist(t_token *tokens)
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