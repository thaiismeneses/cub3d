/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:57:55 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/14 12:25:49 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	**make_portrat(char **map)
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

static int	height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static int	width(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j] != '\0' && map[i][j] != '\n')
		j++;
	return (j);
}

static void	xy_player(char **map, t_map *map_copy)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i] && map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'W' 
				|| map[i][j] == 'S' || map[i][j] == 'E')
			{
					map_copy->x_player = j;
					map_copy->y_player = i;
					break ;
			}
			j++;
		}
		i++;
	}
}

t_map	*struct_map(char **map)
{
	t_map	*copy_map;

	copy_map = ft_calloc(1, sizeof(t_map));
	if (!copy_map)
		return (NULL);
	copy_map->map = map;
	copy_map->height = height(map);
	copy_map->width = width(map);;
	xy_player(map, copy_map);
	return (copy_map);
}
static void	fill_map(t_map *copy_map, int x, int y)
{
	if (x < 0 || x >= copy_map->width || y < 0 || y >= copy_map->height)
		return;
	if (copy_map->map[y][x] == '1')
		return;
	copy_map->map[y][x] = '1';
	fill_map(copy_map, x - 1, y);
	fill_map(copy_map, x + 1, y);
	fill_map(copy_map, x, y - 1);
	fill_map(copy_map, x, y + 1);
}

static int valid_map(t_map *copy_map)
{
	int x;
	int y;

	x = copy_map->x_player;
	y = copy_map->y_player;
	if (!copy_map || !copy_map->map)
		return (MAP_ERROR);
	if (copy_map->map[y - 1][x] == '1' && copy_map->map[y + 1][x] == '1' &&
		copy_map->map[y][x - 1] == '1' && copy_map->map[y][x + 1] == '1')
		return (MAP_ERROR);
	return(NONE_ERROR);
}
int	playable_map(t_mlx_data *data)
{
	t_map	*copy_map;

	copy_map = struct_map(data->map_frame);
	fill_map(copy_map, 1, 1);
	if (valid_map(copy_map) == MAP_ERROR)
	{
		free_matrix(copy_map->map);
		free(copy_map);
		return (MAP_ERROR);
	}
	free_matrix(copy_map->map);
	free(copy_map);
	return (NONE_ERROR);
}