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
	//int i = 0;
	char	**map;
	//t_token *tokens;
	t_mlx_data data;

	data.tokens = NULL;
	if (argc != 2)
		return (error_messages(ARGS_ERROR));
	map = open_fd(argv[1]);
	/*while (map[i])
	{
		printf("-> %s", map[i++]);
		//printf("len: %li\n", ft_strlen(map[i]));
	}*/
	data.tokens = tokenization(map, data.tokens);
	//free_matrix(map);
	//print_token_list(data.tokens);
	if (check_errors(data.tokens) != NONE_ERROR)
		return(free_list(data.tokens), 1);
	//find_player(&data);
	printf("aqui\n");
	data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Cub3D");
	mlx_key_hook(data.win, handle_board, &data);
	mlx_hook(data.win, 17, 0, free_game, &data);
 	mlx_loop(data.mlx);
	return (0);
}
