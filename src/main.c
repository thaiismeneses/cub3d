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
	t_token *tokens;

	tokens = NULL;
	if (argc != 2)
		return (error_messages(ARGS_ERROR));
	map = open_fd(argv[1]);
	/*while (map[i])
    {
        printf("-> %s", map[i++]);
        //printf("len: %li\n", ft_strlen(map[i]));
    }*/
	tokens = tokenization(map, tokens);
	//print_token_list(tokens);
	if (check_errors(tokens) != NONE_ERROR)
        return(free_list(tokens), 1);
	free_list(tokens);
	return (0);
}
