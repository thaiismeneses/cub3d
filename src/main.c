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

void	config(t_mlx_data *data)
{
	find_player(data);
	convert_map(data);
}

int	game_loop(t_mlx_data *data)
{
	render(data);
	draw_minimap(data);
	return (0);
}

int	main(int argc, char **argv)
{
	char	**map;
	t_mlx_data	data;

	data.tokens = NULL;
	if (argc != 2)
		return (error_messages(ARGS_ERROR));
	map = open_fd(argv[1]);
	data.tokens = tokenization(map, data.tokens);
	if (check_errors(&data) != NONE_ERROR)
		return(free_data_struct(&data), 1);
	config(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	mlx_loop_hook(data.mlx, game_loop, &data);
	mlx_key_hook(data.win, handle_board, &data);
	mlx_hook(data.win, 17, 0, free_game, &data);
	mlx_loop(data.mlx);
	return (0);
}
