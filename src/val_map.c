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