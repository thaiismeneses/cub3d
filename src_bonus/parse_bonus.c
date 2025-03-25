/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:12:10 by lfuruno-          #+#    #+#             */
/*   Updated: 2025/01/24 15:12:10 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d_bonus.h"

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
