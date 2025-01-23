/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfranco <thfranco@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:26:13 by thfranco          #+#    #+#             */
/*   Updated: 2025/01/17 18:26:18 by thfranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <fcntl.h>

/*** errors ***/
# define NONE_ERROR 1
# define ARGS_ERROR -1
# define EXTENSION_ERROR -2
# define FD_ERROR -3

/*** validation ***/
int     check_extension(char *argv);
int     error_messages(int error);

/*** map_file ***/
char    **open_fd(char *map_ext);

#endif
