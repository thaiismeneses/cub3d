/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:41:39 by thfranco          #+#    #+#             */
/*   Updated: 2025/02/12 22:28:30 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_board(int keycode, t_mlx_data *data)
{
	moviments(data, keycode);
	if (keycode == XK_Escape)
		free_game(data);
	return (0);
}
