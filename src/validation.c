/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:35:38 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/23 11:35:38 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_extension(char *argv, char *ext)
{
	int		i;
	int		j;

	i = 0;
	j = 3;
	while (argv[i] != '\0')
		i++;
	i--;
	while (j >= 0)
	{
		if (argv[i] != ext[j])
			return (EXTENSION_ERROR);
		i--;
		j--;
	}
	if (i < 0)
		return (EXTENSION_ERROR);
	return (NONE_ERROR);
}

int	error_messages(int error)
{
	ft_putstr_fd("Error\n", 2);
	if (error == -1)
		ft_putstr_fd("Wrong numbers of arguments, expected 2.\n", 2);
	else if (error == -2)
		ft_putstr_fd("Invalid extension path, expected .cub file.\n", 2);
	else if (error == -3)
		ft_putstr_fd("Error opening the map file.\n", 2);
	else if (error == -4)
		ft_putstr_fd("Invalid characters.\n", 2);
	else if (error == -5)
		ft_putstr_fd("Invalid scene description.\n", 2);
	else if (error == -6)
		ft_putstr_fd("Invalid texture file.\n", 2);
	return (error);
}

int	check_errors(t_token *tokens)
{
	if (val_texture(tokens) == TEXTURE_ERROR || verify_order(tokens) == TEXTURE_ERROR
		|| map_exist(tokens) == TEXTURE_ERROR)
		return (error_messages(TEXTURE_ERROR));
	else if (xpm_file(tokens) == PATH_ERROR)
		return(error_messages(PATH_ERROR));
	return (NONE_ERROR);
}