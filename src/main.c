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
	char	**map;

	if (argc != 2)
		return (error_messages(ARGS_ERROR));
	map = open_fd(argv[1]);
	printf("Mapa .cub recebido\n");
	(void) map;
}
