/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:57:55 by thfranco          #+#    #+#             */
/*   Updated: 2025/03/19 17:54:11 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	columns_lines(char **map, t_portrat *portrat)
{
	int		i;
	size_t	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			len--;
		if (portrat->columns < len)
			portrat->columns = len;
		i++;
	}
	portrat->lines = i + 4;
	portrat->columns = portrat->columns + 4;
	return (i);
}

static void	malloc_line(t_portrat *portrat, size_t i)
{
	portrat->map_portrat[i] = malloc(portrat->columns + 2);
	if (!portrat->map_portrat[i])
	{
		while (i > 0)
			free(portrat->map_portrat[--i]);
		free(portrat->map_portrat);
	}
}

void	put_on_portrat(char **map, t_portrat *portrat, size_t i, size_t j)
{
	size_t	original_len;

	if (i < 2 || i >= portrat->lines - 2 || j < 2 || j >= portrat->columns - 2)
	{
		if (i == 0 || i == portrat->lines - 1
			|| j == 0 || j == portrat->columns - 1)
			portrat->map_portrat[i][j] = '1';
		else
			portrat->map_portrat[i][j] = '0';
	}
	else
	{
		original_len = ft_strlen(map[i - 2]);
		if (map[i - 2][original_len - 1] == '\n')
			original_len--;
		if (j - 2 < original_len)
			portrat->map_portrat[i][j] = map[i - 2][j - 2];
		else
			portrat->map_portrat[i][j] = '0';
	}
}

char	**make_portrat(char **map)
{
	size_t		i;
	size_t		j;
	t_portrat	portrat;

	init_portrat(&portrat);
	i = columns_lines(map, &portrat);
	portrat.map_portrat = malloc((portrat.lines + 1) * sizeof(char *));
	if (!portrat.map_portrat)
		return (NULL);
	i = 0;
	while (i < portrat.lines)
	{
		malloc_line(&portrat, i);
		j = 0;
		while (j < portrat.columns)
		{
			put_on_portrat(map, &portrat, i, j);
			j++;
		}
		portrat.map_portrat[i][j] = '\n';
		portrat.map_portrat[i][j + 1] = '\0';
		i++;
	}
	portrat.map_portrat[portrat.lines] = NULL;
	return (portrat.map_portrat);
}
