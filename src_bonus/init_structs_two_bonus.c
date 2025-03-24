/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_two_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:26:20 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/03/19 15:26:25 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

t_map	*struct_map(char **map)
{
	t_map	*copy_map;

	copy_map = ft_calloc(1, sizeof(t_map));
	if (!copy_map)
		return (NULL);
	copy_map->map = map;
	copy_map->height = height(map);
	copy_map->width = width(map);
	xy_player(map, copy_map);
	return (copy_map);
}

void init_portrat(t_portrat *portrat)
{
	portrat->lines = 0;
	portrat->columns = 0;
	portrat->i = 0;
	portrat->j = 0;
	portrat->map_portrat = NULL;
}