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
# include <ctype.h> //apagar

/*** ERRORS ***/
# define NONE_ERROR 1
# define ARGS_ERROR -1
# define EXTENSION_ERROR -2
# define FD_ERROR -3
# define MAP_ERROR -4
# define TEXTURE_ERROR -5
# define PATH_ERROR -6
# define COLOR_ERROR -7

/*** STRUCTS ***/
typedef enum s_type
{
    NO, //0
    SO, //1
    WE, //2
    EA, //3
    F, //4
    C, //5
    NONE, //6
    MAP, //7
}   t_type;

typedef struct s_token
{
    char    *data;
    t_type  type;
    struct s_token   *next;
}   t_token;

/*** validation ***/
int	check_extension(char *argv, char *ext);
int     error_messages(int error);
int	check_errors(t_token *tokens);

/*** map_file ***/
void	free_list(t_token *token);
void	free_matrix(char **matrix);
char    **open_fd(char *map_ext);

/*** elements ***/
t_type	find_type(char *map, int i);
int	type_index(t_type type, int i);
int verify_order(t_token *tokens);
int val_texture(t_token *tokens);

/*** parse ***/
char	*get_token(char *cmd, int i, int start);
t_token	*set_token_list(t_token *data, int type, char *value);
t_token *tokenization(char **map, t_token *data);

/*** val_map.c ***/
int valid_player(t_token *tokens);
int valid_char(t_token *tokens);
int break_map(t_token *tokens);
int map_exist(t_token *tokens);

/*** textures ***/
int rgb_textures(t_token *tokens);
int is_valid_file_path(char *path);
int xpm_file(t_token *tokens);

/*** valid_wall ***/
int valid_wall(t_token *tokens);
char **map_to_matrix(t_token *tokens);

/*** extra_print ***/
void	print_token_list(t_token *head);

#endif
