/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmunoz <gmunoz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:35:21 by guido             #+#    #+#             */
/*   Updated: 2025/07/15 23:23:17 by gmunoz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	append_io_node(t_io_node **io_list, t_io_node *new_node)
{
	t_io_node	*current;

	if (!*io_list)
	{
		*io_list = new_node;
		return ;
	}
	current = *io_list;
	while (current && current->next)
		current = current->next;
	current->next = new_node;
}

t_io_type	get_io_type(t_token_type type)
{
	if (type == T_LESS)
		return (IO_IN);
	if (type == T_GREAT)
		return (IO_OUT);
	if (type == T_DLESS)
		return (IO_HEREDOC);
	return (IO_APPEND);
}

t_io_node	*new_io_node(t_token_type type, char *value)
{
	t_io_node	*new_node;

	new_node = (t_io_node *)ft_calloc(1, sizeof(t_io_node));
	if (!new_node)
		return (NULL);
	new_node->type = get_io_type(type);
	new_node->value = ft_strdup(value);
	if (!new_node->value)
		return (free(new_node), NULL);
	return (new_node);
}

t_node_type	get_node_type(t_token_type type)
{
	if (type == T_AND)
		return (N_AND);
	if (type == T_OR)
		return (N_OR);
	return (N_PIPE);
}

t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	return (node);
}
