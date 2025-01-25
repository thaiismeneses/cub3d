/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:12:10 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/24 15:12:10 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_token(char *cmd, int i, int start)
{
	char	*token;
	int		token_length;

	token_length = i - start;
	token = NULL;
	if (token_length > 0)
	{
		token = (char *)calloc((token_length + 1), sizeof(char));
		ft_strncpy(token, cmd + start, token_length);
		token[token_length] = '\0';
	}
	return (token);
}
static void	add_node(t_token **data, t_type type, char *value)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = NULL;
	last_node = *data;
	if (!data)
		return ;
	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->type = type;
	new_node->data = ft_strdup(value);
	new_node->next = NULL;
	if (!(*data))
		(*data) = new_node;
	else
    {
		while (last_node->next != NULL)
            last_node = last_node->next;
        last_node->next = new_node;
    }
}

t_token	*set_token_list(t_token *data, int type, char *value)
{
	add_node(&data, type, value);
	return (data);
}

t_token *tokenization(char **map, t_token *data)
{
    int i;
    int j;
    int start;
    char *value;
    t_type type;

    i = 0;
    data = NULL;
    if (!**map)
        return (0);
    while(map[i])
    {
        j = 0;
        while (ft_isspace(map[i][j]))
            j++;
        start = j;
        type = find_type(map[i], j);
        j = type_index(type, j);
        while (ft_isspace(map[i][j]))
            j++;
        start = j;
        if (type != MAP)
        {
            while (map[i][j] && map[i][j] != '\0' && !ft_isspace(map[i][j]))
                j++;
        }
        else
        {
            j = 0;
            start = 0;
            while (map[i][j] && map[i][j] != '\0')
                j++;
        }
        value = get_token(map[i], j, start);
        data = set_token_list(data, type, value);
        free(value);
        i++;
    }
    return (data);
}
