/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:44:51 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/23 11:44:51 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_list(t_token *token)
{
	t_token	*current;
	t_token *temp;
	if(!token)
		return ;
	current = token;
	while (current)
	{
		temp = current->next;
		free(current->data);
		current->data = NULL;
		free(current);
		current = temp;
	}
	token = NULL;
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
}

static int	number_lines_fd(char *map_ext)
{
	int		number_lines;
	int		fd;
	char	*line;

	number_lines = 0;
	fd = open(map_ext, O_RDWR);
	if (fd < 0)
	{
		error_messages(FD_ERROR);
		exit(0);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		number_lines += 1;
	}
	close(fd);
	return (number_lines);
}

static char	**read_fd(char *map_ext)
{
	int		i;
	int		num_lines;
	int		fd;
	char	**map;

	i = 0;
	num_lines = number_lines_fd(map_ext);
	map = malloc(sizeof(char *) * (num_lines + 1));
	if (!map)
		return (NULL);
	fd = open(map_ext, O_RDWR);
	if (fd < 0)
	{
		error_messages(FD_ERROR);
		return (NULL);
	}
	while (i < num_lines)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	get_next_line(fd);
	map[i] = NULL;
	close (fd);
	return (map);
}

char	**open_fd(char *map_ext)
{
	char	**map;

	if (check_extension(map_ext, ".cub") == EXTENSION_ERROR)
	{
		error_messages (EXTENSION_ERROR);
		exit(0);
	}
	map = read_fd(map_ext);
	return (map);
}