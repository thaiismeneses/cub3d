/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:01:32 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/27 12:01:32 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void full_matrix(char **matrix, t_token *tokens)
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
            if (!matrix[i])
                break ;
            i++;
        }
        current = current->next;
    }
}

char **map_to_matrix(t_token *tokens)
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
    matrix = malloc(line_count * sizeof(char *));
    if (!matrix)
        return (NULL);
    full_matrix(matrix, tokens);
    return (matrix);
}

static int verify_location(char **map, int i, int j)
{
    if ((i > 0 && (map[i - 1][j] == '1' || map[i - 1][j] == ' ')) ||
        (j > 0 && (map[i][j - 1] == '1' || map[i][j - 1] == ' ')) ||
        (map[i][j + 1] == '1' || map[i][j + 1] == ' ') ||
        (map[i + 1] && (map[i + 1][j] == '1' || map[i + 1][j] == ' ')))
        return (1);
    return (0);
}

static int get_max_width(char **map)
{
    int max_width;
    int width;
    int i;

    max_width = 0;
    i = 0;
    while (map[i])
    {
        width = ft_strlen(map[i]);
        if (width > max_width)
            max_width = width;
        i++;
    }
    return (max_width);
}

static char **fill_zeros(char **map)
{
    int i;
    int j;
    int max_width;
    int num_rows;
    char **new_map;

    i = 0;
    num_rows = 0;
    max_width = get_max_width(map);
    while (map[num_rows])
        num_rows++;
    new_map = malloc(sizeof(char *) * (num_rows + 1));
    if (!new_map)
        return (NULL);
    while (i < num_rows)
    {
        new_map[i] = malloc(sizeof(char) * (max_width + 1));
        if (!new_map[i])
            return (NULL);
        ft_memset(new_map[i], '0', max_width);
        new_map[i][max_width] = '\0';
        j = 0;
        while (map[i][j] != '\0')
        {
            if (map[i][j] == ' ')
            {
                if (verify_location(map, i, j) == 1)
                    new_map[i][j] = '0';
                else 
                    new_map[i][j] = ' ';
            }
            else if (map[i][j] <= 13)
                new_map[i][j] = '0';
            else
                new_map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
    new_map[num_rows] = NULL;
    return (new_map);
}

int valid_wall(t_token *tokens)
{
    int i = 0;
    char **map;
    char **map_zeros;

    map = map_to_matrix(tokens);
    map_zeros = fill_zeros(map);
    free_matrix(map);
    while (map_zeros[i])
    {
        printf("%s\n", map_zeros[i]);
        i++;
    }
    return (NONE_ERROR);
}
