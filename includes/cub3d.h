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
# include <math.h>

/*** ERRORS ***/
# define NONE_ERROR 1
# define ARGS_ERROR -1
# define EXTENSION_ERROR -2
# define FD_ERROR -3
# define CHARACTER_ERROR -4
# define TEXTURE_ERROR -5

/*** STRUCTS ***/
typedef enum s_type
{
    NO, //0
    SO, //1
    WE, //2
    EA, //3
    F, //4
    C, //5
    MAP, //6
}   t_type;

typedef struct s_token
{
    char    *data;
    t_type  type;
    struct s_token   *next;
}   t_token;

/*** validation ***/
int     check_extension(char *argv);
int     error_messages(int error);

/*** map_file ***/
void	free_matrix(char **matrix);
char    **open_fd(char *map_ext);

/*** elements ***/
t_type	find_type(char *map, int i);
int	type_index(t_type type, int i);
char	*get_token(char *cmd, int i, int start);
t_token	*set_token_list(t_token *data, int type, char *value);
t_token *tokenization(char **map, t_token *data);

/*** extra_print ***/
void	print_token_list(t_token *head);

#endif
