/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:26:49 by thfranco          #+#    #+#             */
/*   Updated: 2025/01/17 18:26:56 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("Starting game...\n");
		printf("Map file: %s\n", argv[1]);
	}
	else
	{
		printf("Error: Invalid number of arguments\n");
	}
}
