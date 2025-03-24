/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:55:37 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/24 10:55:37 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_type	find_type(char *map, int i)
{
	if (map[i] == 'N' && map[i + 1] == 'O')
		return (NO);
	if (map[i] == 'S' && map[i + 1] == 'O')
		return (SO);
	if (map[i] == 'W' && map[i + 1] == 'E')
		return (WE);
	if (map[i] == 'E' && map[i + 1] == 'A')
		return (EA);
	if (map[i] == 'F' && map[i + 1] == ' ')
		return (F);
	if (map[i] == 'C' && map[i + 1] == ' ')
		return (C);
	if (map[i] == '\0')
		return (NONE);
	else
		return (MAP);
}

int	type_index(t_type type, int i)
{
	if (type == NO || type == SO || type == WE || type == EA)
		i += 2;
	else if (type == F || type == C)
		i += 1;
	return (i);
}

static int	verify_texture(t_token *tokens, t_type type)
{
	int		i;
	t_token	*current;

	i = 0;
	current = tokens;
	while (current != NULL)
	{
		if (current->type == type)
			i++;
		current = current->next;
	}
	if (i == 1)
		return (1);
	return (0);
}

int	val_rgb(t_token *tokens)
{
	int	f;
	int	c;

	f = 0;
	c = 0;
	f = verify_texture(tokens, F);
	c = verify_texture(tokens, C);
	if (f != 1 || c != 1)
		return (TEXTURE_ERROR);
	return (NONE_ERROR);
}

int	val_texture(t_token *tokens)
{
	int	n;
	int	s;
	int	w;
	int	e;

	n = 0;
	s = 0;
	w = 0;
	e = 0;
	n = verify_texture(tokens, NO);
	s = verify_texture(tokens, SO);
	w = verify_texture(tokens, WE);
	e = verify_texture(tokens, EA);
	if (n != 1 || s != 1 || w != 1 || e != 1)
		return (TEXTURE_ERROR);
	if (val_rgb(tokens) == TEXTURE_ERROR)
		return (TEXTURE_ERROR);
	return (NONE_ERROR);
}
