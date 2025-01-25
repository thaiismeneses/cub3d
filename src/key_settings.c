/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:41:39 by thfranco          #+#    #+#             */
/*   Updated: 2025/01/25 14:42:08 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_board(int keysym, t_mlx_data *data)
{
	if (keysym == 65307)
	{
		printf("ESC pressed\n");
		sleep(1);
		free_game(data);
	}
	return (0);
}
