/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:03:45 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/03/27 18:39:53 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	call_split(char *line)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(line, ' ');
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (i);
}

static void	help_token(char *line, int *start, int *j, t_type type)
{
	if (type == C || type == F)
	{
		while (line[*j])
			(*j)++;
	}
	if (type != MAP)
	{
		while (line[*j] && !ft_isspace(line[*j]))
			(*j)++;
		if (type != NONE && call_split(line) != 2)
		{
			error_messages(TEXTURE_ERROR);
			exit(1);
		}
	}
	else
	{
		*j = 0;
		*start = 0;
		while (line[*j])
			(*j)++;
	}
}

t_token	*process_line(char *line, t_token *data)
{
	int		j;
	int		start;
	char	*value;
	t_type	type;

	j = 0;
	while (ft_isspace(line[j]))
		j++;
	start = j;
	type = find_type(line, j);
	j = type_index(type, j);
	while (ft_isspace(line[j]))
		j++;
	start = j;
	help_token(line, &start, &j, type);
	value = get_token(line, j, start);
	data = set_token_list(data, type, value);
	free(value);
	print_token_list(data);
	return (data);
}

t_token	*tokenization(char **map, t_token *data)
{
	int	i;

	i = 0;
	data = NULL;
	if (!map || !*map)
		return (NULL);
	while (map[i])
	{
		data = process_line(map[i], data);
		i++;
	}
	free_matrix(map);
	return (data);
}
