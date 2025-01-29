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

static char    **make_portrat(char **map)
{
    size_t lines;
    size_t columns;
    size_t i;
    size_t j;
    char **map_portrat;

    i = 0;
    columns = 0;

    // Calcula o número de linhas e a maior largura do mapa original
    while (map[i])
    {
        size_t len = ft_strlen(map[i]);
        if (map[i][len - 1] == '\n') // Ignora '\n' ao calcular largura
            len--;
        if (columns < len)
            columns = len;
        i++;
    }

    // Adiciona 4 ao tamanho original para criar a moldura (2 camadas de cada lado)
    lines = i + 4;
    columns = columns + 4;

    // Aloca memória para o array de ponteiros (incluindo espaço para o NULL final)
    map_portrat = malloc((lines + 1) * sizeof(char *));
    if (!map_portrat)
        return (NULL);

    i = 0;
    while (i < lines)
    {
        // Aloca memória para cada linha (incluindo '\0' no final)
        map_portrat[i] = malloc(columns + 2); // +2 para '\n' e '\0'
        if (!map_portrat[i])
        {
            // Libera a memória alocada anteriormente em caso de falha
            while (i > 0)
                free(map_portrat[--i]);
            free(map_portrat);
            return (NULL);
        }

        j = 0;
        while (j < columns)
        {
            // Adiciona moldura externa de '1' e moldura interna de '0'
            if (i < 2 || i >= lines - 2 || j < 2 || j >= columns - 2)
            {
                if (i == 0 || i == lines - 1 || j == 0 || j == columns - 1)
                    map_portrat[i][j] = '1'; // Primeira camada de '1'
                else
                    map_portrat[i][j] = '0'; // Segunda camada de '0'
            }
            else
            {
                // Copia o mapa original para o centro, removendo '\n' se necessário
                size_t original_len = ft_strlen(map[i - 2]);
                if (map[i - 2][original_len - 1] == '\n')
                    original_len--;

                if (j - 2 < original_len)
                    map_portrat[i][j] = map[i - 2][j - 2];
                else
                    map_portrat[i][j] = '0'; // Preenche espaços vazios com '0'
            }
            j++;
        }

        // Adiciona '\n' no final de cada linha antes do '\0'
        map_portrat[i][j] = '\n';
        map_portrat[i][j + 1] = '\0';

        i++;
    }

    // Define o último elemento da matriz como NULL
    map_portrat[lines] = NULL;

    return (map_portrat);
}

int valid_wall(t_token *tokens)
{
    int i;
    char **map;
    char **map_portrat;

    i = 0;
    map = map_to_matrix(tokens);
    map_portrat = make_portrat(map);
    free_matrix(map);
    while (map_portrat[i])
    {
        printf("-> %s\n", map_portrat[i++]);
        //printf("len: %li\n", ft_strlen(map_portrat[i]));
    }
    return (NONE_ERROR);
}
