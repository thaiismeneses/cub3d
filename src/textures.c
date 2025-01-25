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

int is_valid_file_path(char *path) 
{
    int fd;

	fd = open(path, O_RDONLY);
    if (fd == -1)
        return (PATH_ERROR);
    close(fd);
    return (NONE_ERROR);
}

int xpm_file(t_token *tokens)
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